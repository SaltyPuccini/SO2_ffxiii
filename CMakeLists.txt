cmake_minimum_required(VERSION 3.22)
project(SO2_ffxiii)

set(CMAKE_CXX_STANDARD 14)

add_executable(SO2_ffxiii main.cpp Postac.cpp Postac.h)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
