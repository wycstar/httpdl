#pragma once
#include "HTTPUtil.h"
#include <sstream>
#include <iostream>

class HTTPRequest
{
private:
    void _parse();
    std::string _header;
    HTTPUtil::HTTP_METHOD _method;
    std::string _version;
    std::string _uri;
    HTTPUtil::HTTP_STATUS_CODE _error_code;
    std::map<std::string, std::string> _line_map;
    std::string _accept;
    
public:
    HTTPRequest();
    HTTPRequest(const char *);
    ~HTTPRequest();
    
    HTTPUtil::HTTP_METHOD get_method();
    std::string get_version();
    std::string get_uri();
    HTTPUtil::HTTP_STATUS_CODE get_error();
    HTTPUtil::HTTP_UA get_ua();
    std::string get_mime();
    //HTTPRequest &operator=(HTTPRequest &&other) {

    //};
};
