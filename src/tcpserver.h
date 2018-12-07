#pragma once

class TcpServer {
public:
    void run();
protected:
    explicit TcpServer(unsigned port);
private:
    virtual void service(int sockfd)=0;
    int listen_fd_;
};
