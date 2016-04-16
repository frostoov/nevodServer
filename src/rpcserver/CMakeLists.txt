cmake_minimum_required(VERSION 2.8)
project(nevodserver)

include_directories("${CMAKE_SOURCE_DIR}/include/")

set(rpcserver_files_source
    rpcserver.hpp
    rpcserver.cpp
    easrpc.hpp
    easrpc.cpp
    uranrpc.hpp
    uranrpc.cpp
    dispatcher.hpp
    dispatcher.cpp
    json.hpp
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
    util.hpp
    util.cpp
    reader.hpp
    writer.hpp
    formathandler.hpp
    jsonformathandler.hpp
    jsonformathandler.cpp
)

add_library(rpcserver ${rpcserver_files_source})
