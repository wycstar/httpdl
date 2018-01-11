#pragma once
#include <iostream>
#include <string>
#include <map>
#include "HTTPRequest.h"
#include "log.h"

class HTTPResponse
{
    using HTTP_STRING_MAP = std::map<HTTP_STATUS_CODE, std::string>;
private:
    const std::string _SERVER_STRING;
    const HTTP_STRING_MAP _ERROR_TIP;
    const HTTP_STRING_MAP _ERROR_TYPE;
    HTTP_METHOD _method;
    std::string _version;
    std::string _uri;
    HTTP_STATUS_CODE _error_code;
    int _fd;

public:
    HTTPResponse();
    HTTPResponse(HTTPRequest &&request, int fd);
    std::string make_response(HTTPRequest &request);
    void handle_error(HTTP_STATUS_CODE code);
    ~HTTPResponse();
};
