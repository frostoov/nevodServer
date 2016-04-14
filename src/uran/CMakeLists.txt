cmake_minimum_required(VERSION 2.8)
project(nevodserver)

set(uran_files_source
    uranstation.hpp
    uranstation.cpp
)

add_library(uran ${uran_files_source})
