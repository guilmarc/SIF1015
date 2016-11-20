cmake_minimum_required(VERSION 3.6)
project(SIF1015)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -lpthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -lncurses")

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")

#Bring the headers, such as Student.h into the project
include_directories(src)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#find_package( Threads REQUIRED )
add_executable(TP1Client ${SOURCES})
#target_link_libraries( TP1 Threads::Threads )