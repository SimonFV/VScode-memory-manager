cmake_minimum_required(VERSION 3.8)

project(test)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(SOURCES src/main.cpp)
include_directories(${PROJECT_SOURCE_DIR}/memory_manager/include/)

add_executable(test ${SOURCES})
target_link_libraries(test ${PROJECT_SOURCE_DIR}/memory_manager/build/libmem_manager.so)