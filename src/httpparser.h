//
// Created by lmz on 2018/12/6.
//

#ifndef HELLOW_HTTPPARSER_H
#define HELLOW_HTTPPARSER_H

#include <http_parser.h>
#include <exception>

class HttpParseException : std::exception {
public:
    const char *what() const noexcept override;
};

class HTTPParser {
public:
    virtual ~HTTPParser() = default;

    size_t execute(const char* buf,size_t sz);

protected:
    explicit HTTPParser(http_parser_type t);
    http_parser parser_;

private:
    virtual int on_message_begin() = 0;

    virtual int on_url(const char *, size_t) = 0;

    virtual int on_status(const char *, size_t) = 0;

    virtual int on_header_field(const char *, size_t) = 0;

    virtual int on_header_value(const char *, size_t) = 0;

    virtual int on_headers_complete() = 0;

    virtual int on_body(const char *, size_t) = 0;

    virtual int on_message_complete() = 0;

    virtual int on_chunk_header() = 0;

    virtual int on_chunk_complete() = 0;


    friend int on_message_begin(http_parser *);

    friend int on_headers_complete(http_parser *);

    friend int on_message_complete(http_parser *);

    friend int on_chunk_header(http_parser *);

    friend int on_chunk_complete(http_parser *);

    friend int on_url(http_parser *, const char *, size_t);

    friend int on_status(http_parser *, const char *, size_t);

    friend int on_header_field(http_parser *, const char *, size_t);

    friend int on_header_value(http_parser *, const char *, size_t);

    friend int on_body(http_parser *, const char *, size_t);

};


#endif //HELLOW_HTTPPARSER_H
