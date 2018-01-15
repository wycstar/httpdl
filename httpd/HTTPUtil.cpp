#include "HTTPUtil.h"

HTTPUtil::HTTPUtil()
{
}


HTTPUtil::~HTTPUtil()
{
}

std::string HTTPUtil::now(void)
{
    char buf[50];
    memset(buf, 0, sizeof(buf));
    const time_t stamp = time(NULL);
    struct tm *datetime = gmtime(&stamp);
    strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", datetime);
    return std::string(buf);
}
