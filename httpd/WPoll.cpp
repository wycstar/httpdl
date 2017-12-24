#include "WPoll.h"
#include "log.h"

WPoll::WPoll()
{
    _fd = epoll_create(10000);
}

WPoll::~WPoll()
{
    close(_fd);
}

void WPoll::add(int fd)
{
    struct epoll_event _ev;
    _ev.events = EPOLLIN | EPOLLOUT;
    _ev.data.fd = fd;
    int ret = epoll_ctl(_fd, EPOLL_CTL_ADD, fd, &_ev);
    if (ret != 0) {
        THROW_SYSTEM_ERROR();
    }
}

void WPoll::process()
{

}
