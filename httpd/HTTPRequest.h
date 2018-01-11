#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

typedef enum _tHTTP_STATUS {
    HTTP_OK = 200,
    HTTP_FORBIDDEN = 403,
    HTTP_NOT_FOUND = 404,
    HTTP_SERVER_ERROR = 500
}HTTP_STATUS_CODE;

typedef enum _tHTTP_METHOD {
    GET,
    POST,
    PUT,
    DELETE
}HTTP_METHOD;

typedef struct _tHTTP_UA {
    string os;
    string render;
    string browser_name;
    string browser_core;
    string arch;
}HTTP_UA;

class HTTPRequest
{
private:
    vector<string> _split(const string& source, const string& sign);
    void _parse();
    string _header;
    HTTP_METHOD _method;
    string _version;
    string _uri;
    
public:
    HTTPRequest();
    HTTPRequest(const char *);
    ~HTTPRequest();
    
    inline HTTP_METHOD get_method();
    inline string get_version();
    inline string get_uri();
    HTTP_UA get_ua();
};
