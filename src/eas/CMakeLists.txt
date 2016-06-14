cmake_minimum_required(VERSION 2.8)
project(nevodserver)

set(eas_files_source
    registers.hpp
    registers.cpp
    client.hpp
    queueofmessages.hpp
    realqueueofmessages.hpp
    realqueueofmessages.cpp
    host.hpp
    host.cpp
    master.hpp
    realmaster.hpp
    realmaster.cpp
    easstation.hpp
    easstation.cpp
    adc.hpp
    adc.cpp
    realclient.cpp
    realclient.hpp
)

add_library(eas ${eas_files_source})
