#include "Server.h"
#include "log.h"
#include "Worker.h"
#include "WSocket.h"

Server::Server() :
    _workers(std::shared_ptr<Worker>(new Worker(4))),
    _listen(std::shared_ptr<WSocket>(new WSocket(SOCKET_TYPE::INET))),
    _poll(std::shared_ptr<WPoll>(new WPoll))
{
    _listen->bind();
    _listen->listen();
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
                char buf[1024];
                int read = 0;
                int index = 0;
                while ((read = ::read(handler, buf + index, 1023)) > 0) {
                    index += read;
                }
                if (read == -1 && errno == EAGAIN) {
                    THROW_SYSTEM_ERROR();
                }
                std::cout << buf << std::endl;
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
