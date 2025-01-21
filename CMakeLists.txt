cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MyProject)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем директории для заголовочных файлов
include_directories(include)

# Сканируем все файлы .cpp в директории src
file(GLOB SRC_FILES "src/*.cpp")

# Добавляем исполняемый файл
add_executable(main ${SRC_FILES})

# Добавляем Google Test
# Предполагается, что Google Test установлен в системе
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Сканируем все файлы .cpp в директории tests
file(GLOB TEST_FILES "tests/*.cpp")

# Создаем исполняемый файл для тестов
add_executable(runTests ${TEST_FILES} ${SRC_FILES})

# Линкуем тесты с Google Test и pthread
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# Включаем тестирование
enable_testing()

# Добавляем тесты
add_test(NAME HelloTest COMMAND runTests)
