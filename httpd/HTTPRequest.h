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
    std::multimap<std::string, std::string> _query_params;
    void _parse_url_params(std::string &uri);
    void _parse_request_line(std::string &line);
    void _parse_request_header(std::vector<std::string> &container);
    
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
    
};
