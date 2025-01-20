#include <gtest/gtest.h>
#include "../src/main.cpp" // Подключаем ваш основной код

TEST(HelloWorldTest, BasicAssertions) {
    testing::internal::CaptureStdout(); // Захватываем стандартный вывод
    sayHello();
    std::string output = testing::internal::GetCapturedStdout(); // Получаем вывод
    EXPECT_EQ(output, "Hello, World!\n"); // Проверяем вывод
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}