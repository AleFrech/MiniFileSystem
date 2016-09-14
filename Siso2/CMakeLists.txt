cmake_minimum_required(VERSION 3.6)
project(Siso2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp BitMap.cpp BitMap.h Directory.cpp Directory.h FileAttributes.cpp FileAttributes.h PartitionManager.cpp PartitionManager.h Block.cpp Block.h FileManager.cpp FileManager.h)
add_executable(Siso2 ${SOURCE_FILES})