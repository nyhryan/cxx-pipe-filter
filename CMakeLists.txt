cmake_minimum_required(VERSION 3.26)
project(cxx-pipe-and-filter)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Pipe.hpp
    src/Filter.hpp
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/src/file.txt
    ${CMAKE_CURRENT_BINARY_DIR}/file.txt)