cmake_minimum_required(VERSION 3.12)
project(hellow)

set(CMAKE_CXX_STANDARD 11)

add_executable(hellow main.cpp httpparser.cpp httpparser.h httprequestparser.cpp httprequestparser.h httprequest.cpp httprequest.h tcpserver.cpp tcpserver.h)
target_link_libraries(${PROJECT_NAME} libgo http_parser)