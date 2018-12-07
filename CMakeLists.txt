cmake_minimum_required(VERSION 3.10)
project(hellow)

set(CMAKE_CXX_STANDARD 14)
aux_source_directory(src SRC_DIR)

add_executable(hellow ${SRC_DIR})
target_link_libraries(${PROJECT_NAME} libgo http_parser dl pthread)
