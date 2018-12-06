#include <libgo/coroutine.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "httprequestparser.h"

static const uint16_t port = 8080;

void echo_server() {
    int accept_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t len = sizeof(addr);
    if (-1 == bind(accept_fd, (sockaddr *) &addr, len)) {
        fprintf(stderr, "bind error, please change the port value.\n");
        exit(1);
    }
    if (-1 == listen(accept_fd, 5)) {
        fprintf(stderr, "listen error.\n");
        exit(1);
    }

    for(;;){
        int sockfd=accept(accept_fd,(sockaddr*)&addr,&len);
        if(sockfd==-1){
            if(EAGAIN==errno||EINTR==errno)
                continue;
            fprintf(stderr,"accpect error:%s\n",strerror(errno));
            return;
        }
        auto fun=[sockfd]{
            HttpRequestParser parser;
            HttpRequest request;
            char buf[4096];
            ssize_t n;
            for(;;){
                n=read(sockfd,buf,sizeof(buf));
                if(n==0)
                    break;
                if(n==-1){
                    if(EAGAIN==errno||EINTR==errno){
                        continue;
                    }
                    fprintf(stderr,"read error:%s\n",strerror(errno));
                    break;
                }
                try{
                    parser.execute(buf,n);
                    if(parser.isMessageFinished())
                    {
                        request=parser.getRequest();
                        break;
                    }
                }
                catch (const std::exception& e)
                {
                    fprintf(stderr,"%s\n",e.what());
                    break;
                }

            }
            close(sockfd);
        };
        go fun;
    }
}


int main() {
    go echo_server;

    // 单线程执行
    co_sched.Start(0);
    return 0;
}