
cmake_minimum_required(VERSION 3.6)
project(SIF1015_TP1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES ./src/main.c)
add_executable(TP1 ./src/main.c)