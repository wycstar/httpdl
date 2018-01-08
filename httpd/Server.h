#pragma once
#include "WPoll.h"
#include "WSocket.h"
#include "Worker.h"

class Server
{
private:
    WPoll _poll;
    std::shared_ptr<WSocket> _listen;
    std::shared_ptr<Worker> workers;

public:
    Server();
    ~Server();
    void dispatch();
    static void listen_handler(int epoll_fd, int listen_fd, WPoll& poll);
};
