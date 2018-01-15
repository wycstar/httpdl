#pragma once
#include "HTTPUtil.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <map>

class HTTPRequest
{
private:
    std::vector<std::string> _split(const std::string& source, const std::string& sign);
    void _parse();
    std::string _header;
    HTTP_METHOD _method;
    std::string _version;
    std::string _uri;
    HTTP_STATUS_CODE _error_code;
    
public:
    HTTPRequest();
    HTTPRequest(const char *);
    ~HTTPRequest();
    
    HTTP_METHOD get_method();
    std::string get_version();
    std::string get_uri();
    HTTP_STATUS_CODE get_error();
    HTTP_UA get_ua();
    //HTTPRequest &operator=(HTTPRequest &&other) {

    //};
};
