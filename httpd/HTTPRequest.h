#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>

typedef enum _tHTTP_STATUS {
    HTTP_OK = 200,
    HTTP_BAD_REQUEST = 400,
    HTTP_FORBIDDEN = 403,
    HTTP_NOT_FOUND = 404,
    HTTP_SERVER_ERROR = 500,
    HTTP_METHOD_NOT_IMPLEMENTED = 501,
    HTTP_UNSUPPORTED_VERSION = 505
}HTTP_STATUS_CODE;

typedef enum _tHTTP_METHOD {
    GET,
    POST,
    PUT,
    DELETE,
    UNIMPLEMENTED
}HTTP_METHOD;

typedef struct _tHTTP_UA {
    std::string os;
    std::string render;
    std::string browser_name;
    std::string browser_core;
    std::string arch;
}HTTP_UA;

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
