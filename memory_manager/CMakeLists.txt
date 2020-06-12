cmake_minimum_required(VERSION 3.8)

project(memory_manager)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(source
    src/VSPtr.cpp
)
set(headers
    include/VSPtr.hpp
    include/control.hpp
    include/counter.hpp
    include/g_collector.hpp
    include/data_type.hpp
)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(mem_manager SHARED ${source} ${headers})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(mem_manager Threads::Threads)