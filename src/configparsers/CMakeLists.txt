cmake_minimum_required(VERSION 2.8)
project(nevodserver)

set(configparsers_files_source
    serverconfig.hpp
    serverconfig.cpp
    stationconfig.hpp
    stationconfig.cpp
    configrecord.hpp
)

add_library(configparsers ${configparsers_files_source})
target_include_directories(configparsers PUBLIC ${CMAKE_SOURCE_DIR}/include)
