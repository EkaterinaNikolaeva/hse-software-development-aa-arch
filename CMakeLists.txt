cmake_minimum_required(VERSION 3.10)

project(hello)

add_executable(hello src/main.cpp src/Hello.cpp)

target_link_libraries(hello gtest)

include_directories(include)