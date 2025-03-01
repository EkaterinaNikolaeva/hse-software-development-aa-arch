cmake_minimum_required(VERSION 3.10)

project(IRSQ_Project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/rsq_library/include)
include_directories(${CMAKE_SOURCE_DIR}/rsq_library/utils)
include_directories(${CMAKE_SOURCE_DIR}/experiment_environment/include)


find_package(benchmark REQUIRED)
find_package(nlohmann_json REQUIRED)


add_executable(my_benchmark
        experiment_environment/src/irsq_benchmark.cpp
)

target_link_libraries(my_benchmark
        benchmark::benchmark
        nlohmann_json::nlohmann_json
)

target_compile_definitions(my_benchmark PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")

include_directories(${CMAKE_SOURCE_DIR}/experiment_environment/include)

add_subdirectory(rsq_library/tests)

