#include "tcpserver.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <cstdlib>
#include <libgo/coroutine.h>
#include <thread>


void TcpServer::run(){
    std::thread t{[]{co_sched.Start(4,1024);}};
    t.detach();
    sockaddr_in addr;
    socklen_t len=sizeof(addr);
    int enable = 1;
    for(;;){
        int sockfd=accept(listen_fd_,(sockaddr*)&addr,&len);
        if(-1==sockfd){
            if(EAGAIN==errno||EINTR==errno)
                continue;
            fprintf(stderr,"accept error:%s\n",strerror(errno));
            return;
        }
        setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable));
        go [sockfd,this]{
            this->service(sockfd);
        };
    }
}

TcpServer::TcpServer(unsigned port){
    listen_fd_=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=htonl(INADDR_ANY);
    socklen_t len=sizeof(addr);
    if(-1==bind(listen_fd_,reinterpret_cast<sockaddr*>(&addr),len)){
        fprintf(stderr,"bind error:%s\n",strerror(errno));
        exit(1);
    }
    if(-1==listen(listen_fd_,1000)){
        fprintf(stderr,"listen error.\n");
        exit(1);
    }
}
