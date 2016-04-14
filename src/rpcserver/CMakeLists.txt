cmake_minimum_required(VERSION 2.8)
project(nevodserver)

include_directories("${CMAKE_SOURCE_DIR}/include/")

set(rpcserver_files_source
    rpcserver.hpp
    rpcserver.cpp
)

add_library(rpcserver ${rpcserver_files_source})
target_link_libraries(rpcserver xsonrpc)
