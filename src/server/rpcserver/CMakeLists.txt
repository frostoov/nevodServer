cmake_minimum_required(VERSION 2.8)
project(nevodserver)

set(rpcserver_files_source
    dispatcher.hpp
    dispatcher.cpp
    jsonconstants.hpp
    jsonreader.hpp
    jsonreader.cpp
    jsonwriter.hpp
    jsonwriter.cpp
    server.hpp
    server.cpp
    tcpconnection.cpp
    tcpconnection.hpp
    fault.hpp
    request.hpp
    request.cpp
    response.hpp
    response.cpp
    value.hpp
    value.cpp
)

add_library(rpcserver ${rpcserver_files_source})
target_include_directories(rpcserver PUBLIC ${CMAKE_SOURCE_DIR}/include)
