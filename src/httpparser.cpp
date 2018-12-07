//
// Created by lmz on 2018/12/6.
//

#include <libgo/coroutine.h>
#include <functional>
#include "httpparser.h"

int on_message_begin(http_parser *httpParser) {
    auto parser = reinterpret_cast<HTTPParser *>(httpParser->data);
    return parser->on_message_begin();
}

int on_url(http_parser *httpParser, const char *buf, size_t sz) {
    auto parser = reinterpret_cast<HTTPParser *>(httpParser->data);
    return parser->on_url(buf, sz);
}

int on_status(http_parser *httpParser, const char *buf, size_t sz) {
    auto parser = reinterpret_cast<HTTPParser *>(httpParser->data);
    return parser->on_status(buf, sz);
}

int on_header_field(http_parser *httpParser, const char *buf, size_t sz) {
    auto parser = reinterpret_cast<HTTPParser *>(httpParser->data);
    return parser->on_header_field(buf, sz);
}

int on_header_value(http_parser *httpParser, const char *buf, size_t sz) {
    auto parser = reinterpret_cast<HTTPParser *>(httpParser->data);
    return parser->on_header_value(buf, sz);
}

int on_body(http_parser *httpParser, const char *buf, size_t sz) {
    auto parser = reinterpret_cast<HTTPParser *>(httpParser->data);
    return parser->on_body(buf, sz);
}

int on_headers_complete(http_parser *httpParser) {
    auto parser = reinterpret_cast<HTTPParser *>(httpParser->data);
    return parser->on_headers_complete();
}

int on_message_complete(http_parser *httpParser) {
    auto parser = reinterpret_cast<HTTPParser *>(httpParser->data);
    return parser->on_message_complete();
}

int on_chunk_header(http_parser *httpParser) {
    auto parser = reinterpret_cast<HTTPParser *>(httpParser->data);
    return parser->on_chunk_header();
}

int on_chunk_complete(http_parser *httpParser) {
    auto parser = reinterpret_cast<HTTPParser *>(httpParser->data);
    return parser->on_chunk_complete();
}

static http_parser_settings settings{
    on_message_begin,
            on_url,
            on_status,
            on_header_field,
            on_header_value,
            on_headers_complete,
            on_body,
            on_message_complete,
            on_chunk_header,
            on_chunk_complete
};


size_t HTTPParser::execute(const char* buf,size_t sz) {
    auto s=http_parser_execute(&parser_,&settings,buf,sz);
    if(s!=sz)
        throw HttpParseException();
    return s;
}

HTTPParser::HTTPParser(http_parser_type t){
    http_parser_init(&parser_, t);
    parser_.data = this;
}

const char *HttpParseException::what() const noexcept{
    return "parse exception";
}
