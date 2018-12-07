#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <memory>
#include "tcpserver.h"

class HttpRequest;
class HttpResponse;

class HttpServer:public TcpServer
{
public:
    HttpServer(unsigned port=80);
    // TcpServer interface
private:
    void service(int sockfd) override;
    void dispatch(const HttpRequest&, HttpResponse&);
};

#endif // HTTPSERVER_H
