cmake_minimum_required(VERSION 3.6)
project(Client)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pthread -lncurses")

set(SOURCE_FILES src/client.c src/screen.c)

add_executable(Client ${SOURCE_FILES})


#Bring the headers, such as Student.h into the project
#include_directories(src)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#find_package( Threads REQUIRED )
#target_link_libraries( TP1 Threads::Threads )