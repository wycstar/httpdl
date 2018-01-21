#include "HTTPResponse.h"
#include <sstream>
#include <sys/socket.h>
#include "WFile.h"

void HTTPResponse::_execute_cgi()
{
}

HTTPResponse::HTTPResponse()
{
}

HTTPResponse::HTTPResponse(HTTPRequest && request, int fd, std::string &base) :
    _fd(fd),
    _base(base),
    _method(request.get_method()),
    _uri(request.get_uri()),
    _version(request.get_version()),
    _accept(request.get_mime()),
    _error_code(request.get_error())
{

}

void HTTPResponse::make_response()
{
    if (_error_code != HTTPUtil::HTTP_OK) handle_error(_error_code);
    switch (_method) {
        case HTTPUtil::GET: {
            std::cout << "--------------" << std::endl;
            std::cout << "URI:" << _uri << std::endl;
            //May be more elegant
            WFile f(_base + _uri);
            if (f.error() != HTTPUtil::HTTP_OK) {
                handle_error(f.error());
                return;
            }
            if (f.is_dir()) {
                _uri += "/index.html";
            }
            WFile g(_base + _uri);
            if (g.error() != HTTPUtil::HTTP_OK) {
                handle_error(HTTPUtil::HTTP_FORBIDDEN);
                return;
            }
            make_header(HTTPUtil::HTTP_OK);
            send(_fd, g.data(), g.size(), 0);
            //std::cout << "SEND BYTE:" << send(_fd, "ab1234", strlen("ab1234") + 1, 0) << std::endl;
            break;
        };
        case HTTPUtil::POST: {

            break;
        };
        case HTTPUtil::PUT: {

            break;
        };
        case HTTPUtil::DELETE: {

            break;
        };
        default: {
            handle_error(HTTPUtil::HTTP_METHOD_NOT_IMPLEMENTED);
        }
    }
    close(_fd);
    return;
}

void HTTPResponse::handle_error(HTTPUtil::HTTP_STATUS_CODE code)
{
    auto tip = HTTPUtil::DEFAULT_ERROR_PAGE.find(code);
    make_header(code);
    send(_fd, tip->second.c_str(), tip->second.length(), 0);
}

void HTTPResponse::make_header(HTTPUtil::HTTP_STATUS_CODE code)
{
    std::stringstream ss;
    auto type = HTTPUtil::RESPONSE_LINE.find(code);
    ss << (code == HTTPUtil::HTTP_UNSUPPORTED_VERSION ? "HTTP/1.1" : "HTTP/" + _version)
        << " " << code << " " << type->second
        << "Server:" << HTTPUtil::SERVER_STRING << "\r\n"
        << "Date:" << HTTPUtil::now() << "\r\n"
        << "Content-Type:" << _accept << "\r\n"
        << "\r\n";
    std::cout << "RESPONSE HEADER:" << ss.str() << std::endl;
    send(_fd, ss.str().c_str(), ss.str().length(), 0);
}

HTTPResponse::~HTTPResponse()
{
}
