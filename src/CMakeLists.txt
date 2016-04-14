cmake_minimum_required(VERSION 2.8)
project(nevodserver)

add_subdirectory(eas)
add_subdirectory(uran)
add_subdirectory(rpcserver)
add_subdirectory(keeper)

include_directories("${CMAKE_SOURCE_DIR}/include/")

set(src_files_source main.cpp)

add_executable(${PROJECT_NAME} ${src_files_source})
target_link_libraries(${PROJECT_NAME} rpcserver)
