cmake_minimum_required(VERSION 2.8)
project(nevodserver)

add_subdirectory(mocks)
add_subdirectory(testclasses)

set(catch_files
    ${CMAKE_SOURCE_DIR}/include
)

set(test_files
    rpcserver.cpp
    configparsers.cpp
    keeper.cpp
    eas.cpp
)

add_library(catch INTERFACE)
target_include_directories(catch INTERFACE ${catch_files})

add_executable(Test ${test_files})
target_link_libraries(Test catch)
target_link_libraries(Test testclasses)
target_link_libraries(Test mocks)
