//
// Created by lmz on 2018/12/6.
//

#ifndef HELLOW_HTTPREQUESTPARSER_H
#define HELLOW_HTTPREQUESTPARSER_H

#include "httpparser.h"
#include "httprequest.h"

class HttpRequestParser : public HTTPParser {
public:
    explicit HttpRequestParser(HttpRequest &);

    bool isMessageFinished() const {
        return message_finished_;
    }

    HttpRequest getRequest();

private:
    int on_message_begin() override;

    int on_url(const char *string, size_t size) override;

    int on_status(const char *string, size_t size) override;

    int on_header_field(const char *string, size_t size) override;

    int on_header_value(const char *string, size_t size) override;

    int on_headers_complete() override;

    int on_body(const char *string, size_t size) override;

    int on_message_complete() override;

    int on_chunk_header() override;

    int on_chunk_complete() override;

private:
    HttpRequest& request_;
    bool message_finished_;

};


#endif //HELLOW_HTTPREQUESTPARSER_H
