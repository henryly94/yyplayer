cmake_minimum_required(VERSION 3.1)
project(player)


add_subdirectory(Common)
include_directories("Common")

add_subdirectory(Renderer)
include_directories("Renderer")

add_subdirectory(Decoder)
include_directories("Decoder")

add_subdirectory(Application)
include_directories("Application")
