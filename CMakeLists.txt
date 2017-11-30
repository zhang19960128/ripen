cmake_minimum_required(VERSION 3.0)
project(mdsimulate)
file(GLOB SOURCE "${CMAKE_BINARY_DIR}/../src/*.cpp")
set(SOURCE ${SOURCE})
set(CMAKE_CXX_FLAGS "-std=c++11")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}$/..)
include_directories("${CMAKE_BINARY_DIR}/../head")
add_executable(mdsimulate ${SOURCE}
	${CMAKE_BINARY_DIR}/../main.cpp)
