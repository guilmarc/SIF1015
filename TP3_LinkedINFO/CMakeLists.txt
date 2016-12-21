cmake_minimum_required(VERSION 3.6)
project(Sockets)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pthread")

#However, the file(GLOB...) allows for wildcard additions:
add_subdirectory("client")
add_subdirectory("server")