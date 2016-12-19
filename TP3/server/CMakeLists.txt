cmake_minimum_required(VERSION 3.6)
project(Server)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pthread")

#However, the file(GLOB...) allows for wildcard additions:
#add_subdirectory("src/client")
#add_subdirectory("src/server")

#set(CLIENT_SOURCE_FILES client.c)
set(SOURCE_FILES src/server.c)

#add_executable(Client ${CLIENT_SOURCE_FILES})
add_executable(Server ${SOURCE_FILES})



#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -lpthread")




#Bring the headers, such as Student.h into the project
#include_directories(src)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#find_package( Threads REQUIRED )
#target_link_libraries( TP1 Threads::Threads )