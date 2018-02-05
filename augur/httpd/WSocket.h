#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <string>

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
    void bind(std::string host = "0.0.0.0", unsigned short port = 54213);
    void connect(std::string host, short port);
    int native();
    void listen();
    void to_none_blocking();
    static void to_none_blocking(int fd);
    void read(uint8_t *buf, size_t len);
};

