cmake_minimum_required(VERSION 3.10)
project(HelloWorld)

# Укажите стандарт C++
set(CMAKE_CXX_STANDARD 11)

# Добавляем основной исполняемый файл
add_executable(hello_world src/main.cpp)

# Находим Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Добавляем тесты
add_executable(runTests test/test_main.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# Указываем зависимости для тестов
add_dependencies(runTests hello_world)
