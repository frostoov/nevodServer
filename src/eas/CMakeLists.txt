cmake_minimum_required(VERSION 2.8)
project(nevodserver)

set(eas_files_source
    registers.hpp
    registers.cpp
    client.hpp
    client.cpp
    queueofmessages.hpp
    queueofmessages.cpp
    host.hpp
    host.cpp
    master.hpp
    master.cpp
    easstation.hpp
    easstation.cpp
    adc.hpp
    adc.cpp
    hostclient.cpp
    hostclient.hpp
)

add_library(eas ${eas_files_source})
