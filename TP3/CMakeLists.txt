cmake_minimum_required(VERSION 3.6)
project(Sockets)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pthread")

#However, the file(GLOB...) allows for wildcard additions:
add_subdirectory("client")
add_subdirectory("server")

#set(CLIENT_SOURCE_FILES client.c)
#set(SERVER_SOURCE_FILES server.c)

#add_executable(Client ${CLIENT_SOURCE_FILES})
#add_executable(Server ${SERVER_SOURCE_FILES})



#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -lpthread")



#Bring the headers, such as Student.h into the project
#include_directories(src)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY client/bin)

#find_package( Threads REQUIRED )
#target_link_libraries( TP1 Threads::Threads )