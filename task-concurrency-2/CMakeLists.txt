cmake_minimum_required(VERSION 3.16)
project(HistogramParallel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(histogram histogram.cpp)
target_link_libraries(histogram Threads::Threads)

add_executable(histogram_mutex histogram_mutex.cpp)
target_link_libraries(histogram_mutex Threads::Threads)

add_executable(histogram_atomic histogram_atomic.cpp)
target_link_libraries(histogram_atomic Threads::Threads)

add_executable(histogram_local histogram_local.cpp)
target_link_libraries(histogram_local Threads::Threads)
