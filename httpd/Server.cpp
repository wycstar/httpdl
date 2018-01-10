#include "Server.h"
#include "log.h"
#include "HTTPRequest.h"

Server::Server() :
    _workers(std::shared_ptr<Worker>(new Worker(4))),
    _listen(std::shared_ptr<WSocket>(new WSocket(SOCKET_TYPE::INET))),
    _poll(std::shared_ptr<WPoll>(new WPoll))
{
    _listen->bind();
    _listen->listen();
    _poll->add(_listen->native());
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
                _workers->commit(request_handler, handler);
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

void Server::request_handler(int client_fd)
{
    char buf[1024];
    int read = 0;
    int index = 0;
    bzero(buf, sizeof(buf));
    while ((read = ::read(client_fd, buf + index, sizeof(buf) - 1)) > 0) {
        index += read;
    }
    if (strlen(buf) == 0) return;
    std::cout << "abc" << std::endl;
    HTTPRequest r(buf);
    //std::cout << r.get_uri() << r.get_version() << std::endl;
}
