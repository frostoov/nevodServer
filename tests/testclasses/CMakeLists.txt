cmake_minimum_required(VERSION 2.8)
project(nevodserver)

set(testclasses_files_source
    tcpconnectiontest.hpp
    tcpconnectiontest.cpp
    rpcservertest.hpp
    rpcservertest.cpp
)

include_directories(${Boost_INCLUDE_DIR})

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system)

add_library(testclasses ${testclasses_files_source})
target_link_libraries(testclasses boost_system)
target_link_libraries(testclasses server)
target_link_libraries(testclasses eas)
target_link_libraries(testclasses observer)
