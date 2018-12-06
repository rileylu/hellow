//
// Created by lmz on 2018/12/6.
//

#ifndef HELLOW_HTTPREQUEST_H
#define HELLOW_HTTPREQUEST_H

#include <string>
#include <list>

struct HttpHeader {
    HttpHeader(const std::string &key, const std::string &value)
            : key{key}, value{value} {}

    std::string key;
    std::string value;
};

struct HttpRequest {
    HttpRequest()= default;
    HttpRequest(HttpRequest&& other)
    :method(std::move(other.method))
    ,url(std::move(other.url))
    ,body(std::move(other.body))
    ,flags(other.flags)
    ,major(other.major)
    ,minor(other.minor)
    ,headerList(std::move(other.headerList))
    {
    }
    HttpRequest& operator=(HttpRequest&& other){
        method=std::move(other.method);
        url=std::move(other.url);
        body=std::move(other.body);
        flags=other.flags;
        major=other.major;
        minor=other.minor;
        headerList=std::move(other.headerList);
        return *this;
    }
    std::string method;
    std::string url;
    std::string body;
    unsigned flags;
    unsigned short major;
    unsigned short minor;
    std::list<HttpHeader> headerList;
};

#endif //HELLOW_HTTPREQUEST_H
