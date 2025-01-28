find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB TEST_FILES "*.cpp")

add_executable(runTests ${TEST_FILES})

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

enable_testing()

add_test(NAME IRSQTest COMMAND runTests)
