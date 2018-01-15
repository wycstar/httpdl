#include "HTTPResponse.h"
#include <sstream>
#include <sys/socket.h>
#include "WFile.h"

HTTPResponse::HTTPResponse()
{
}

HTTPResponse::HTTPResponse(HTTPRequest && request, int fd, std::string &base) :
    _fd(fd),
    _base(base),
    _SERVER_STRING("Augur"),
    _ERROR_TIP({
        { HTTP_NOT_FOUND , "<HTML><TITLE>404 NOT FOUND</TITLE>\r\n<BODY><P>server can't find the source which you request\r\n</P></BODY></HTML>\r\n" },
        { HTTP_BAD_REQUEST , "<HTML><HEAD><TITLE>400 BAD REQUEST</TITLE></HEAD><BODY><P>this is a bad request for server</P></BODY></HTML>" },
        { HTTP_FORBIDDEN , "<HTML><TITLE>403 PERMISSION DENIED</TITLE>\r\n<BODY><P>you don't have enough permissions to view this file\r\n</P></BODY></HTML>\r\n" },
        { HTTP_SERVER_ERROR , "<HTML><HEAD><TITLE>500 SERVER ERROR</TITLE></HEAD><BODY><P>SERVER ERROR</P></BODY></HTML>" },
        { HTTP_METHOD_NOT_IMPLEMENTED , "<HTML><HEAD><TITLE>METHOD NOT IMPLEMENTED\r\n</TITLE></HEAD>\r\n<BODY><P>request method not support\r\n</P></BODY></HTML>\r\n" },
        { HTTP_UNSUPPORTED_VERSION , "<HTML><HEAD><TITLE>WRONG HTTP VERSION\r\n</TITLE></HEAD>\r\n<BODY><P>HTTP version not support\r\n</P></BODY></HTML>\r\n" }
        }),
    _ERROR_TYPE({
        { HTTP_OK, "OK\r\n" },
        { HTTP_NOT_FOUND , "Not Found\r\n" },
        { HTTP_BAD_REQUEST , "Bad Request\r\n" },
        { HTTP_FORBIDDEN , "Forbidden\r\n" },
        { HTTP_SERVER_ERROR , "Server Error\r\n" },
        { HTTP_METHOD_NOT_IMPLEMENTED , "Method Not Implemented\r\n" },
        { HTTP_UNSUPPORTED_VERSION , "HTTP Version Not Supported\r\n" }
        }),
    _method(request.get_method()),
    _uri(request.get_uri()),
    _version(request.get_version()),
    _error_code(request.get_error())
{

}

void HTTPResponse::make_response()
{
    if (_error_code != HTTP_OK) handle_error(_error_code);
    switch (_method) {
        case HTTP_METHOD::GET: {
            std::cout << "--------------" << std::endl;
            std::cout << "URI:" << _uri << std::endl;
            //May be more elegant
            WFile f(_base + _uri);
            if (f.error() != HTTP_OK) {
                handle_error(f.error());
                return;
            }
            if (f.is_dir()) {
                _uri += "/index.html";
            }
            WFile g(_base + _uri);
            if (g.error() != HTTP_OK) {
                handle_error(HTTP_FORBIDDEN);
                return;
            }
            //std::cout << std::string(g.data()) << std::endl;
            make_header(HTTP_OK);
            //send(_fd, g.data(), g.size(), 0);
            std::cout << "SEND BYTE:" << send(_fd, "ab1234", strlen("ab1234") + 1, 0) << std::endl;
            break;
        };
        case HTTP_METHOD::POST: {

            break;
        };
        case HTTP_METHOD::PUT: {

            break;
        };
        case HTTP_METHOD::DELETE: {

            break;
        };
        default: {
            handle_error(HTTP_METHOD_NOT_IMPLEMENTED);
        }
    }
    close(_fd);
    return;
}

void HTTPResponse::handle_error(HTTP_STATUS_CODE code)
{
    HTTP_STRING_MAP::const_iterator tip = _ERROR_TIP.find(code);
    make_header(code);
    send(_fd, tip->second.c_str(), tip->second.length(), 0);
}

void HTTPResponse::make_header(HTTP_STATUS_CODE code)
{
    std::stringstream ss;
    HTTP_STRING_MAP::const_iterator type = _ERROR_TYPE.find(code);
    ss << (code == HTTP_UNSUPPORTED_VERSION ? "HTTP/1.1" : "HTTP/" + _version)
        << " " << code << " " << type->second
        << "Server:" << _SERVER_STRING << "\r\n"
        << "Date:" << HTTPUtil::now() << "\r\n"
        << "Content-Type:text/html\r\n"
        << "\r\n";
    std::cout << "RESPONSE HEADER:" << ss.str() << std::endl;
    send(_fd, ss.str().c_str(), ss.str().length(), 0);
}

HTTPResponse::~HTTPResponse()
{
}
