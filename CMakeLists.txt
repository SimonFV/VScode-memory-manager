cmake_minimum_required(VERSION 3.8)

project(test)

set(CMAKE_CXX_STANDARD_REQUIRED 14)
include_directories(${PROJECT_SOURCE_DIR}/memory_manager/include)

set(SOURCES src/main.cpp)

add_executable(test ${SOURCES})
target_link_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/memory_manager)
target_link_libraries(test PUBLIC mem_manager)