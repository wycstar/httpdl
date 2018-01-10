#include <cstdio>
#include "Server.h"
#include <iostream>
#include "Config.h"

int main()
{
    //Server server;
    //server.dispatch();
    Config c("/home/wyc/code/httpd/config.conf");
    string ip;
    ip = c.read<string>("ip");
    cout << ip << endl;
    return 0;
}