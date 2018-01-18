#include "Server.h"
#include "log.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "Config.h"

Server::Server() :
    _workers(std::shared_ptr<Worker>(new Worker(4))),
    _listen(std::shared_ptr<WSocket>(new WSocket(SOCKET_TYPE::INET))),
    _poll(std::shared_ptr<WPoll>(new WPoll))
{
    _listen->bind();
    _listen->listen();
    _poll->add(_listen->native(), false);
    Config config("./config");
    _base = config.read("root", _base);
}

Server::~Server()
{

}

void Server::dispatch()
{
    while (true) {
        int count = _poll->wait();
        if (count == -1 && errno == EINTR) {
            THROW_SYSTEM_ERROR();
        }
        auto buffer = _poll->events();
        for (int i = 0; i < count; i++) {
            int handler = buffer[i].data.fd;
            if (handler == _listen->native()) {
                _workers->commit(listen_handler, handler, _poll);
            }
            else {
                _workers->commit(request_handler, handler, _base, _poll);
            }
        }
    }
}

void Server::listen_handler(int listen_fd, std::shared_ptr<WPoll> poll)
{
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int client_fd = ::accept(listen_fd, (struct sockaddr *)&client_addr, &len);
    poll.get()->add(client_fd);
}

void Server::request_handler(int client_fd, std::string &base, std::shared_ptr<WPoll> poll)
{
    char buf[1024];
    bzero(buf, sizeof(buf));
    auto ret = recv(client_fd, buf, sizeof(buf) - 1, 0);
    if (ret == 0) {
        close(client_fd);
        return;
    }
    else if (ret < 0 && errno == EAGAIN) {
        poll.get()->reset_oneshot(client_fd);
        return;
    }
    cout << buf << endl;
    HTTPResponse r(HTTPRequest(buf), client_fd, base);
    r.make_response();
}
