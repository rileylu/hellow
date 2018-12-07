#include <libgo/coroutine.h>
#include "httpserver.h"
#include "httpresponse.h"
#include "httprequestparser.h"

HttpServer::HttpServer(unsigned port)
    :TcpServer (port)
{
}

void HttpServer::service(int sockfd)
{
    HttpRequest req;
    HttpRequestParser httpRequestParser(req);
    char buf[4096];
    ssize_t n;
    bool ok=true;
    for(;;){
        n=read(sockfd,buf,sizeof(buf));
        if(n==0)
            break;
        if(n==-1){
            if(EAGAIN==errno||EINTR==errno)
                continue;
            fprintf(stderr,"read error:%s\n",strerror(errno));
            ok=false;
            break;
        }
        try {
            httpRequestParser.execute(buf,n);
            if(httpRequestParser.isMessageFinished())
                break;
        } catch (const HttpParseException& e) {
            ok=false;
            fprintf(stderr,"%s\n",e.what());
            break;
        }
    }
    if(ok&&httpRequestParser.isMessageFinished())
    {
        HttpResponse rep(sockfd);
        dispatch(req,rep);
    }
    else
    {
        close(sockfd);
    }
}

void HttpServer::dispatch(const HttpRequest &req, HttpResponse &rep)
{
   rep.send();
}
