cmake_minimum_required(VERSION 3.1)
project(player)

set(SOURCE_FILES main.cpp)

add_subdirectory(Common)
include_directories("Common")

add_executable(player ${SOURCE_FILES})
target_link_libraries(player Common)

install(TARGETS player DESTINATION bin)
