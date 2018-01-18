#pragma once
#include <string>
#include <string.h>
#include <time.h>
#include <map>
#include <vector>

namespace HTTPUtil {
    using QUALITY_FACTOR = std::pair<std::string, float>;
    const std::string SERVER_STRING = "Augur";
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
    const std::map<HTTPUtil::HTTP_STATUS_CODE, std::string> DEFAULT_ERROR_PAGE = {
        { HTTP_NOT_FOUND , "<HTML><TITLE>404 NOT FOUND</TITLE>\r\n<BODY><P>server can't find the source which you request\r\n</P></BODY></HTML>\r\n" },
        { HTTP_BAD_REQUEST , "<HTML><HEAD><TITLE>400 BAD REQUEST</TITLE></HEAD><BODY><P>this is a bad request for server</P></BODY></HTML>" },
        { HTTP_FORBIDDEN , "<HTML><TITLE>403 PERMISSION DENIED</TITLE>\r\n<BODY><P>you don't have enough permissions to view this file\r\n</P></BODY></HTML>\r\n" },
        { HTTP_SERVER_ERROR , "<HTML><HEAD><TITLE>500 SERVER ERROR</TITLE></HEAD><BODY><P>SERVER ERROR</P></BODY></HTML>" },
        { HTTP_METHOD_NOT_IMPLEMENTED , "<HTML><HEAD><TITLE>METHOD NOT IMPLEMENTED\r\n</TITLE></HEAD>\r\n<BODY><P>request method not support\r\n</P></BODY></HTML>\r\n" },
        { HTTP_UNSUPPORTED_VERSION , "<HTML><HEAD><TITLE>WRONG HTTP VERSION\r\n</TITLE></HEAD>\r\n<BODY><P>HTTP version not support\r\n</P></BODY></HTML>\r\n" }
    };
    const std::map<HTTPUtil::HTTP_STATUS_CODE, std::string> RESPONSE_LINE = {
        { HTTP_OK, "OK\r\n" },
        { HTTP_NOT_FOUND , "Not Found\r\n" },
        { HTTP_BAD_REQUEST , "Bad Request\r\n" },
        { HTTP_FORBIDDEN , "Forbidden\r\n" },
        { HTTP_SERVER_ERROR , "Server Error\r\n" },
        { HTTP_METHOD_NOT_IMPLEMENTED , "Method Not Implemented\r\n" },
        { HTTP_UNSUPPORTED_VERSION , "HTTP Version Not Supported\r\n" }
    };
    typedef struct _tHTTP_TIME {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        time_t stamp;
        _tHTTP_TIME(void) {};
        _tHTTP_TIME(struct tm *tm) {
            year = tm->tm_year + 1900;
            month = tm->tm_mon + 1;
            day = tm->tm_mday;
            hour = tm->tm_hour;
            minute = tm->tm_min;
            second = tm->tm_sec;
            stamp = mktime(tm);
        };
    }HTTP_TIME;
    std::string now();
    HTTP_TIME to_time(std::string time);
    void quality_sort(std::vector<QUALITY_FACTOR> &a);
    std::vector<QUALITY_FACTOR> parse_mime(std::string mime);
    std::vector<std::string> split(const std::string& source, const std::string& sign);
    const std::map<std::string, std::string> MIME_TYPE_MAP = {
        
    };
}
