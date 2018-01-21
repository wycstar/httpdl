#include <cstdio>
#include "Server.h"
#include <iostream>
#include "Config.h"
#include "FastCGI.h"

int main()
{
    //Server server;
    //server.dispatch();
    std::shared_ptr<WSocket> socket = std::make_shared<WSocket>(SOCKET_TYPE::INET);
    socket->connect("127.0.0.1", 9000);
    /*FCGI::begin_request(socket->native(), 1);
    FCGI::set_env(socket->native(), 1, "SCRIPT_FILENAME", "/home/wyc/code/html/index.php");
    FCGI::set_env(socket->native(), 1, "REQUEST_METHOD", "GET");
    FCGI::end_request(socket->native(), 1);*/
    std::map<std::string, std::string> params = {
        {"SCRIPT_FILENAME", "/home/wyc/code/html/index.php"},
        {"REQUEST_METHOD", "GET"}
    };
    FCGI::write(socket->native(), 1, params);
    FCGI::read(socket->native());
    return 0;
}