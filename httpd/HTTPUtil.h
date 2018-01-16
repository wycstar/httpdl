#pragma once
#include <string>
#include <string.h>
#include <time.h>
#include <map>
#include <vector>

namespace HTTPUtil {
    using QUALITY_FACTOR = std::pair<std::string, float>;
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
