#pragma once
#include "HTTPUtil.h"
#include <iostream>
#include "HTTPRequest.h"
#include "log.h"

class HTTPResponse
{
    using HTTP_STRING_MAP = std::map<HTTPUtil::HTTP_STATUS_CODE, std::string>;
private:
    int _fd;
    std::string _base;
    const std::string _SERVER_STRING;
    const HTTP_STRING_MAP _ERROR_TIP;
    const HTTP_STRING_MAP _ERROR_TYPE;
    HTTPUtil::HTTP_METHOD _method;
    std::string _uri;
    std::string _version;
    std::string _accept;
    HTTPUtil::HTTP_STATUS_CODE _error_code;
    
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
