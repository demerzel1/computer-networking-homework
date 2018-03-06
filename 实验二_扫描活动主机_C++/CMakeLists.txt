cmake_minimum_required(VERSION 3.9)
project(scanhost)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_DEBUG  "-O1 -g")
link_libraries(ws2_32 wsock32)

add_executable(scanhost scanhost.h scanhost.cpp)