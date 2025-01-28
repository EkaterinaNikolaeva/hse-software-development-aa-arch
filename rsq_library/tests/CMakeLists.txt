find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB TEST_FILES "*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/rsq_library/tests/include)

add_executable(runTests ${TEST_FILES})

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

enable_testing()

add_test(NAME IRSQTest COMMAND runTests)
add_test(NAME RandomIRSQTest COMMAND runTests)
