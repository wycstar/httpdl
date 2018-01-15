#pragma once
#include <string>
#include <string.h>
#include <time.h>

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

typedef struct _tHTTP_TIME {
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
}HTTP_TIME;

class HTTPUtil
{
public:
    HTTPUtil();
    ~HTTPUtil();
    static std::string now();
};
