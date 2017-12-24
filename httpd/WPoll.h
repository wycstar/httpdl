#pragma once
#include <sys/epoll.h>
#include <unistd.h>

class WPoll
{
private:
    int _fd;

public:
    WPoll();
    ~WPoll();
    void add(int fd);
    void process();
};

