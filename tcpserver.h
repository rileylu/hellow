//
// Created by lmz on 2018/12/6.
//

#ifndef HELLOW_TCPSERVER_H
#define HELLOW_TCPSERVER_H


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TcpServer {
public:
    TcpServer(unsigned port){
        listen_fd_=socket(AF_INET,SOCK_STREAM,0);
        sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        addr.sin_addr.s_addr=htonl(INADDR_ANY);
        socklen_t len=sizeof(addr);
        if(-1==bind(listen_fd_,(sockaddr*)&addr,len))
    }
    void accept(){

    }
private:
    int listen_fd_;

};


#endif //HELLOW_TCPSERVER_H
