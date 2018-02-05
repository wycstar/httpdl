#include "HTTPUtil.h"
#include <memory>
#include <algorithm>
#include <iostream>

std::string HTTPUtil::now(void)
{
    char buf[50];
    memset(buf, 0, sizeof(buf));
    const time_t stamp = time(NULL);
    struct tm *datetime = gmtime(&stamp);
    strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", datetime);
    return std::string(buf);
}

HTTPUtil::HTTP_TIME HTTPUtil::to_time(std::string time)
{
    struct tm * tm = new struct tm;
    strptime(time.c_str(), "%a, %d %b %Y %H:%M:%S GMT", tm);
    HTTP_TIME a(tm);
    delete tm;
    return a;
}

void HTTPUtil::quality_sort(std::vector<QUALITY_FACTOR>& a)
{
    sort(a.begin(), a.end(), [](QUALITY_FACTOR & x, QUALITY_FACTOR & y){return x.second > y.second; });
}

std::vector<HTTPUtil::QUALITY_FACTOR> HTTPUtil::parse_mime(std::string mime)
{
    std::vector<std::string> a = split(mime, ",");
    std::vector<QUALITY_FACTOR> b;
    for (auto d = a.begin(); d != a.end(); d++) {
        auto sep = d->find_first_of(";");
        b.push_back(QUALITY_FACTOR(d->substr(0, sep), sep == std::string::npos ? 1.0 : atof(d->substr(sep + 3, d->length()).c_str())));
    }
    quality_sort(b);
    return b;
}

std::vector<std::string> HTTPUtil::split(const std::string & source, const std::string & sign)
{
    std::vector<std::string> result;
    std::string::size_type p1, p2;
    p2 = source.find(sign);
    p1 = 0;
    while (std::string::npos != p2) {
        result.push_back(source.substr(p1, p2 - p1));
        p1 = p2 + sign.size();
        p2 = source.find(sign, p1);
    }
    if (p1 != source.size()) {
        result.push_back(source.substr(p1));
    }
    return result;
}
