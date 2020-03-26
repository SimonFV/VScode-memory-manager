cmake_minimum_required(VERSION 3.8)

project(memory_manager)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(source
    src/VSPtr.cpp
)
set(headers
    include/VSPtr.hpp
)

add_library(mem_manager SHARED ${source} ${headers})

target_include_directories(mem_manager PUBLIC ${PROJECT_SOURCE_DIR}/include)