cmake_minimum_required(VERSION 2.8)
project(nevodserver)

include_directories(${nevodserver_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(src)
