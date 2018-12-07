#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H


class HttpResponse
{
public:
    explicit HttpResponse(int sockfd)
        :sockfd_{sockfd}
    {
    }
    HttpResponse(HttpResponse&&);
    HttpResponse& operator=(HttpResponse&&);

    void send();

private:
    HttpResponse(const HttpResponse&)=delete;
    HttpResponse& operator=(const HttpResponse&)=delete;
    int sockfd_;
};

#endif // HTTPRESPONSE_H
