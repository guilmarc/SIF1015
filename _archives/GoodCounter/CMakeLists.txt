cmake_minimum_required(VERSION 3.6)
project(GoodCounter)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pthread")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(SOURCE_FILES goodcounter.c)
#find_package( Threads REQUIRED )
add_executable(GoodCounter ${SOURCE_FILES})
#target_link_libraries( GoodCounter Threads::Threads )