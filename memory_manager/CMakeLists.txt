cmake_minimum_required(VERSION 3.8)

project(memory_manager)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(source
    src/VSPtr.cpp
)
set(headers
    include/VSPtr.hpp
    include/g_collector.hpp
    include/ptr_list.hpp
)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(mem_manager SHARED ${source} ${headers})