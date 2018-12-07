#include "httpserver.h"

int main(){
    HttpServer server(18080);
    server.run();
}
