cmake_minimum_required(VERSION 3.10)

project(IRSQ_Project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/rsq_library/include)

find_package(benchmark REQUIRED)
add_executable(my_benchmark experiment_environment/src/irsq_benchmark.cpp)
target_link_libraries(my_benchmark benchmark::benchmark)

add_subdirectory(rsq_library/tests)

