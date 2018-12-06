//
// Created by lmz on 2018/12/6.
//

#include "httprequestparser.h"

HttpRequestParser::HttpRequestParser()
        :HTTPParser(HTTP_REQUEST),message_finished_(false)
{
}

int HttpRequestParser::on_message_begin() {
    return 0;
}

int HttpRequestParser::on_url(const char *buf, size_t sz) {
    request_.url=std::string(buf,sz);
    request_.method=http_method_str((http_method)parser_.method);
    request_.major=parser_.http_major;
    request_.minor=parser_.http_minor;
    return 0;
}

int HttpRequestParser::on_status(const char *buf, size_t sz) {
    return 0;
}

int HttpRequestParser::on_header_field(const char *buf, size_t sz) {
    request_.headerList.emplace_back(std::string{buf,sz},"");
    return 0;
}

int HttpRequestParser::on_header_value(const char *buf, size_t sz) {
    request_.headerList.back().value=std::string{buf,sz};
    return 0;
}

int HttpRequestParser::on_headers_complete() {
    return 0;
}

int HttpRequestParser::on_body(const char *buf, size_t sz) {
    request_.body=std::string{buf,sz};
    return 0;
}

int HttpRequestParser::on_message_complete() {
    message_finished_=true;
    return 0;
}

int HttpRequestParser::on_chunk_header() {
    return 0;
}

int HttpRequestParser::on_chunk_complete() {
    return 0;
}

HttpRequest HttpRequestParser::getRequest() {
    return std::move(request_);
}

