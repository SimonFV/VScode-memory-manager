cmake_minimum_required(VERSION 3.8)

project(memory_manager)

set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(source
    src/main.cpp
    src/md5.cpp
)
set(headers
    include/server.hpp
    include/md5.h
    include/VSPtr.hpp
    include/control.hpp
    include/counter.hpp
    include/g_collector.hpp
    include/data_type.hpp
)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(run ${source} ${headers})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(run Threads::Threads)