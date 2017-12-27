#include "WPoll.h"
#include "log.h"
#include "Buffer.h"

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
    _listen = fd;
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
    auto r = make_buffer<struct epoll_event>(MAX_EVENTS);
    while(true) {
        int count = epoll_wait(_fd, r.get(), MAX_EVENTS, -1);
        if (count == -1 && errno == EINTR) {
            THROW_SYSTEM_ERROR();
        }
        auto buffer = r.get();
        for (int i = 0; i < count; i++) {
            int handler = buffer[i].data.fd;
            if (handler == _listen) {

            }
        }
    }
}
