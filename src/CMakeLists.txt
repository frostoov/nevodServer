cmake_minimum_required(VERSION 2.8)
project(nevodserver)

add_subdirectory(eas)
add_subdirectory(server)
add_subdirectory(keeper)
add_subdirectory(observer)
add_subdirectory(configparsers)

set(src_files_source
    main.cpp
)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system)

include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${src_files_source})
target_link_libraries(${PROJECT_NAME} server)
target_link_libraries(${PROJECT_NAME} eas)
target_link_libraries(${PROJECT_NAME} observer)
target_link_libraries(${PROJECT_NAME} configparsers)
target_link_libraries(${PROJECT_NAME} boost_system)
