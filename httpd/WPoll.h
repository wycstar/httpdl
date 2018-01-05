#pragma once
#include <sys/epoll.h>
#include <unistd.h>

class WPoll
{
private:
    int _fd;
    int _listen;
    static const int MAX_EVENTS = 32768;

public:
    WPoll();
    WPoll(int listen_fd);
    ~WPoll();
    void add(int fd);
    void process();
    static void establish(int epoll_fd, int socket_fd);
};

