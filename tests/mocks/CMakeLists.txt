cmake_minimum_required(VERSION 2.8)
project(nevodserver)

set(mocks_files_source
    clienttorpcserver.hpp
    clienttorpcserver.cpp

)

add_library(mocks ${mocks_files_source})
target_include_directories(mocks PUBLIC ${CMAKE_SOURCE_DIR}/include)
