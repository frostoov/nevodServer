cmake_minimum_required(VERSION 2.8)
project(nevodserver)

add_subdirectory(rpcserver)

set(server_files_source
    server.hpp
    server.cpp
)

add_library(server ${server_files_source})
target_link_libraries(server rpcserver)
