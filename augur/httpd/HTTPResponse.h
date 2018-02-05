#pragma once
#include "HTTPUtil.h"
#include <iostream>
#include "HTTPRequest.h"
#include "log.h"

class HTTPResponse
{
private:
    int _fd;
    std::string _base;
    HTTPRequest _request;
    void _execute_cgi();
    
public:
    HTTPResponse();
    HTTPResponse(HTTPRequest &&request, int fd, std::string &base);
    void make_response();
    void handle_error(HTTPUtil::HTTP_STATUS_CODE code);
    void make_header(HTTPUtil::HTTP_STATUS_CODE code);
    ~HTTPResponse();
};

class HTTPDate {

};
