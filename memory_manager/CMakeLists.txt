cmake_minimum_required(VERSION 3.8)

project(memory_manager)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(source
    src/main.cpp
)
set(headers
    include/header.hpp
)

add_library(_mem_manager SHARED ${source} ${headers})

target_include_directories(_mem_manager PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(exe ${source} ${headers})

target_link_libraries(exe _mem_manager)