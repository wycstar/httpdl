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
        { ".a", "application/octet-stream" },
        { ".a", "application/octet-stream" },
        { ".ai", "application/postscript" },
        { ".aif", "audio/x-aiff" },
        { ".aiff", "audio/x-aiff" },
        { ".asc", "application/pgp-signature" },
        { ".asf", "video/x-ms-asf" },
        { ".asm", "text/x-asm" },
        { ".asx", "video/x-ms-asf" },
        { ".atom", "application/atom+xml" },
        { ".au", "audio/basic" },
        { ".avi", "video/x-msvideo" },
        { ".bat", "application/x-msdownload" },
        { ".bin", "application/octet-stream" },
        { ".bmp", "image/bmp" },
        { ".bz2", "application/x-bzip2" },
        { ".c", "text/x-c" },
        { ".cab", "application/vnd.ms-cab-compressed" },
        { ".cc", "text/x-c" },
        { ".chm", "application/vnd.ms-htmlhelp" },
        { ".class", "application/octet-stream" },
        { ".com", "application/x-msdownload" },
        { ".conf", "text/plain" },
        { ".cpp", "text/x-c" },
        { ".crt", "application/x-x509-ca-cert" },
        { ".css", "text/css" },
        { ".csv", "text/csv" },
        { ".cxx", "text/x-c" },
        { ".deb", "application/x-debian-package" },
        { ".der", "application/x-x509-ca-cert" },
        { ".diff", "text/x-diff" },
        { ".djv", "image/vnd.djvu" },
        { ".djvu", "image/vnd.djvu" },
        { ".dll", "application/x-msdownload" },
        { ".dmg", "application/octet-stream" },
        { ".doc", "application/msword" },
        { ".dot", "application/msword" },
        { ".dtd", "application/xml-dtd" },
        { ".dvi", "application/x-dvi" },
        { ".ear", "application/java-archive" },
        { ".eml", "message/rfc822" },
        { ".eps", "application/postscript" },
        { ".exe", "application/x-msdownload" },
        { ".f", "text/x-fortran" },
        { ".f77", "text/x-fortran" },
        { ".f90", "text/x-fortran" },
        { ".flv", "video/x-flv" },
        { ".for", "text/x-fortran" },
        { ".gem", "application/octet-stream" },
        { ".gemspec", "text/x-script.ruby" },
        { ".gif", "image/gif" },
        { ".gz", "application/x-gzip" },
        { ".h", "text/x-c" },
        { ".hh", "text/x-c" },
        { ".htm", "text/html" },
        { ".html", "text/html" },
        { ".ico", "image/vnd.microsoft.icon" },
        { ".ics", "text/calendar" },
        { ".ifb", "text/calendar" },
        { ".iso", "application/octet-stream" },
        { ".jar", "application/java-archive" },
        { ".java", "text/x-java-source" },
        { ".jnlp", "application/x-java-jnlp-file" },
        { ".jpeg", "image/jpeg" },
        { ".jpg", "image/jpeg" },
        { ".js", "application/javascript" },
        { ".json", "application/json" },
        { ".log", "text/plain" },
        { ".m3u", "audio/x-mpegurl" },
        { ".m4v", "video/mp4" },
        { ".man", "text/troff" },
        { ".mathml", "application/mathml+xml" },
        { ".mbox", "application/mbox" },
        { ".mdoc", "text/troff" },
        { ".me", "text/troff" },
        { ".mid", "audio/midi" },
        { ".midi", "audio/midi" },
        { ".mime", "message/rfc822" },
        { ".mml", "application/mathml+xml" },
        { ".mng", "video/x-mng" },
        { ".mov", "video/quicktime" },
        { ".mp3", "audio/mpeg" },
        { ".mp4", "video/mp4" },
        { ".mp4v", "video/mp4" },
        { ".mpeg", "video/mpeg" },
        { ".mpg", "video/mpeg" },
        { ".ms", "text/troff" },
        { ".msi", "application/x-msdownload" },
        { ".odp", "application/vnd.oasis.opendocument.presentation" },
        { ".ods", "application/vnd.oasis.opendocument.spreadsheet" },
        { ".odt", "application/vnd.oasis.opendocument.text" },
        { ".ogg", "application/ogg" },
        { ".p", "text/x-pascal" },
        { ".pas", "text/x-pascal" },
        { ".pbm", "image/x-portable-bitmap" },
        { ".pdf", "application/pdf" },
        { ".pem", "application/x-x509-ca-cert" },
        { ".pgm", "image/x-portable-graymap" },
        { ".pgp", "application/pgp-encrypted" },
        { ".pkg", "application/octet-stream" },
        { ".pl", "text/x-script.perl" },
        { ".pm", "text/x-script.perl-module" },
        { ".png", "image/png" },
        { ".pnm", "image/x-portable-anymap" },
        { ".ppm", "image/x-portable-pixmap" },
        { ".pps", "application/vnd.ms-powerpoint" },
        { ".ppt", "application/vnd.ms-powerpoint" },
        { ".ps", "application/postscript" },
        { ".psd", "image/vnd.adobe.photoshop" },
        { ".py", "text/x-script.python" },
        { ".qt", "video/quicktime" },
        { ".ra", "audio/x-pn-realaudio" },
        { ".rake", "text/x-script.ruby" },
        { ".ram", "audio/x-pn-realaudio" },
        { ".rar", "application/x-rar-compressed" },
        { ".rb", "text/x-script.ruby" },
        { ".rdf", "application/rdf+xml" },
        { ".roff", "text/troff" },
        { ".rpm", "application/x-redhat-package-manager" },
        { ".rss", "application/rss+xml" },
        { ".rtf", "application/rtf" },
        { ".ru", "text/x-script.ruby" },
        { ".s", "text/x-asm" },
        { ".sgm", "text/sgml" },
        { ".sgml", "text/sgml" },
        { ".sh", "application/x-sh" },
        { ".sig", "application/pgp-signature" },
        { ".snd", "audio/basic" },
        { ".so", "application/octet-stream" },
        { ".svg", "image/svg+xml" },
        { ".svgz", "image/svg+xml" },
        { ".swf", "application/x-shockwave-flash" },
        { ".t", "text/troff" },
        { ".tar", "application/x-tar" },
        { ".tbz", "application/x-bzip-compressed-tar" },
        { ".tcl", "application/x-tcl" },
        { ".tex", "application/x-tex" },
        { ".texi", "application/x-texinfo" },
        { ".texinfo", "application/x-texinfo" },
        { ".text", "text/plain" },
        { ".tif", "image/tiff" },
        { ".tiff", "image/tiff" },
        { ".torrent", "application/x-bittorrent" },
        { ".tr", "text/troff" },
        { ".txt", "text/plain" },
        { ".vcf", "text/x-vcard" },
        { ".vcs", "text/x-vcalendar" },
        { ".vrml", "model/vrml" },
        { ".war", "application/java-archive" },
        { ".wav", "audio/x-wav" },
        { ".weba", "audio/webm" },
        { ".webm", "video/webm" },
        { ".wma", "audio/x-ms-wma" },
        { ".wmv", "video/x-ms-wmv" },
        { ".wmx", "video/x-ms-wmx" },
        { ".wrl", "model/vrml" },
        { ".wsdl", "application/wsdl+xml" },
        { ".xbm", "image/x-xbitmap" },
        { ".xhtml", "application/xhtml+xml" },
        { ".xls", "application/vnd.ms-excel" },
        { ".xml", "application/xml" },
        { ".xpm", "image/x-xpixmap" },
        { ".xsl", "application/xml" },
        { ".xslt", "application/xslt+xml" },
        { ".yaml", "text/yaml" },
        { ".yml", "text/yaml" },
        { ".zip", "application/zip" }
    };
}
