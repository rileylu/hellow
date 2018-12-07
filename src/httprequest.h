#pragma once
#include <map>
class HttpRequest{
public:
    HttpRequest()=default;
    std::string getMethod() const;
    std::string getUrl() const;
    std::string getBody() const;
private:
    friend class HttpRequestParser;

    std::string method_;
    std::string url_;
    std::string body_;
    std::map<std::string,std::string> headers_;
};
