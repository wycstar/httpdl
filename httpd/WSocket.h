#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

using namespace std;

typedef enum _tSOCKET_TYPE {
    UNIX,
    INET
}SOCKET_TYPE;

class WSocket
{
private:
    int _fd;
    SOCKET_TYPE _type;
    struct sockaddr_in _addr;

public:
    WSocket();
    WSocket(SOCKET_TYPE t);
    ~WSocket();
    void bind(string host, short port);
    void listen();
    void to_none_blocking();
    void read(uint8_t *buf, uint32_t len);
};

