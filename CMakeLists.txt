cmake_minimum_required(VERSION 2.8)

project(final)
SET (CMAKE_C_COMPILER             "/usr/bin/clang")
SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set (LIBS "-pthread -lboost_system -lboost_thread")

aux_source_directory(src SRCS)
file (GLOB HEADERS "./include/*.h*")
include_directories(include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpermissive")

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} ${LIBS})

