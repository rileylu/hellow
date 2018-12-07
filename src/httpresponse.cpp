#include "httpresponse.h"
#include <libgo/coroutine.h>

void HttpResponse::send()
{
    std::string res="HTTP/1.1 200 OK\r\nContent-Length: 24\r\n\r\nthis is hello servlet!!!\r\n";
    write(sockfd_,res.c_str(),res.length());
    close(sockfd_);
}
