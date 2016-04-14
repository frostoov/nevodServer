cmake_minimum_required(VERSION 2.8)
project(nevodserver)

set(eas_files_source
    easstation.hpp
    easstation.cpp
)

add_library(eas ${eas_files_source})
