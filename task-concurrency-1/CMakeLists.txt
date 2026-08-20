cmake_minimum_required(VERSION 3.16)
project(LivelockSimulation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(livelock livelock.cpp)
target_link_libraries(livelock Threads::Threads)

add_executable(fix_scoped_lock fix_scoped_lock.cpp)
target_link_libraries(fix_scoped_lock Threads::Threads)

add_executable(fix_backoff fix_backoff.cpp)
target_link_libraries(fix_backoff Threads::Threads)
