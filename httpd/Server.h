#pragma once
#include "WPoll.h"
#include "WSocket.h"
#include "Worker.h"

class Server
{
private:
    std::shared_ptr<Worker> _workers;
    std::shared_ptr<WSocket> _listen;
    std::shared_ptr<WPoll> _poll;
    std::string _base;

public:
    Server();
    ~Server();
    void dispatch();
    static void listen_handler(int listen_fd, std::shared_ptr<WPoll> poll);
    static void request_handler(int client_fd, std::string &base, std::shared_ptr<WPoll> poll);
};
