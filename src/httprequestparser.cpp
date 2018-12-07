//
// Created by lmz on 2018/12/6.
//

#include "httprequestparser.h"
static std::string last_head;

HttpRequestParser::HttpRequestParser(HttpRequest &request)
        :HTTPParser(HTTP_REQUEST),request_(request),message_finished_(false)
{
}

int HttpRequestParser::on_message_begin() {
    return 0;
}

int HttpRequestParser::on_url(const char *buf, size_t sz) {
    request_.url_=std::string(buf,sz);
    request_.method_=http_method_str((http_method)parser_.method);
    return 0;
}

int HttpRequestParser::on_status(const char *, size_t ) {
    return 0;
}

int HttpRequestParser::on_header_field(const char *buf, size_t sz) {
    last_head=std::string{buf,sz};
    request_.headers_.emplace(last_head,"");

    return 0;
}

int HttpRequestParser::on_header_value(const char *buf, size_t sz) {
    request_.headers_[last_head]=std::string{buf,sz};
    return 0;
}

int HttpRequestParser::on_headers_complete() {
    return 0;
}

int HttpRequestParser::on_body(const char *buf, size_t sz) {
    request_.body_=std::string{buf,sz};
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

