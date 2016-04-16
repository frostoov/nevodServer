cmake_minimum_required(VERSION 2.8)
project(nevodserver)

set(observer_files_source
    observer.hpp
    observer.cpp
)

add_library(observer ${observer_files_source})
