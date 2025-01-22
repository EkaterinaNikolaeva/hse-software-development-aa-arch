#include <gtest/gtest.h>

#include "Hello.hpp"

TEST(HelloWorldTest, BasicAssertions) {
  testing::internal::CaptureStdout();  // Захватываем стандартный вывод
  Hello::sayHello();
  std::string output =
      testing::internal::GetCapturedStdout();  // Получаем вывод
  EXPECT_EQ(output, "Hello, World!\n");        // Проверяем вывод
}