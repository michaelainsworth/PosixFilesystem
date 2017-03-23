# Recent cmake version
cmake_minimum_required(VERSION 3.6)

# Project name and settings
project(PosixFilesystem)
include_directories(source)

# Use C++11 and warn about everything.
set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11 ${CMAKE_CXX_FLAGS}")

# Generate the compile_commands.json file so that YouCompleteMe (a vim
# plugin) knows how to perform semantic auto-completion.
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# Library sources
file(GLOB
    sources
    source/PosixFilesystem/*.cpp)

# Build library
add_library(PosixFilesystem ${sources})

# Example sources
file(GLOB
    example_sources
    example/*.cpp)

# Build examples
foreach(example_source ${example_sources})
    get_filename_component(example_filename_we ${example_source} NAME_WE)
    add_executable(${example_filename_we} ${example_source})
    target_link_libraries(${example_filename_we} PosixFilesystem)
endforeach()

