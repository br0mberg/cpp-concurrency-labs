cmake_minimum_required(VERSION 3.16)
project(AsyncLogger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

# Раскомментируйте после создания async_logger.h и async_logger.cpp:

# add_executable(test_basic test_basic.cpp async_logger.cpp)
# target_link_libraries(test_basic Threads::Threads)

# add_executable(test_concurrent test_concurrent.cpp async_logger.cpp)
# target_link_libraries(test_concurrent Threads::Threads)

# add_executable(test_shutdown test_shutdown.cpp async_logger.cpp)
# target_link_libraries(test_shutdown Threads::Threads)
