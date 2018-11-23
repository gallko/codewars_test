cmake_minimum_required(VERSION 3.5)
project(pthreads)

set(CMAKE_CXX_STANDARD 14)

find_package (Threads)

add_executable(pthreads main.cpp)
target_link_libraries (pthreads ${CMAKE_THREAD_LIBS_INIT})