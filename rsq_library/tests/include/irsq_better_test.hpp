#ifndef IRSQ_BETTER_TEST_HPP
#define IRSQ_BETTER_TEST_HPP

#include <gtest/gtest.h>
#include <consistency_checker.hpp>
#include <irsq.hpp>
#include <naive.hpp>
#include <random_data_generator.hpp>
#include <segment_tree.hpp>

namespace rsq::tests {

template <typename T>
class IRSQBetterTest : public ::testing::Test {
protected:
    // Тест проверяет работу на векторе большого размера
    void TestBigVectorSize() {
        constexpr size_t BIG_VECTOR_SIZE = 1000000;
        utils::RandomDataGenerator generator(BIG_VECTOR_SIZE);
        std::vector<int> input_data = generator.GenerateRandomVector();
        utils::RSQConsistencyChecker<T> checker(input_data);

        checker.CheckQuery(
            0, BIG_VECTOR_SIZE - 1
        );  // проверяем, что сразу после построения корректна сумма в массиве

        checker.SimpleCheckUpdate(0, generator.GetRandomInt());

        checker.SimpleCheckUpdate(
            BIG_VECTOR_SIZE - 1,
            generator.GetRandomInt()  // изменяем последний элемент
        );

        std::size_t random_index = generator.GetRandomIndex();
        int random_value = generator.GetRandomInt();
        checker.SimpleCheckUpdate(random_index, random_value);

        checker.CheckQuery(0, BIG_VECTOR_SIZE - 1);  // сумма на всем массиве
    };

    // проверяем корректность на небольшом векторе с большими позитивными
    // числами
    void TestBigPositiveNumbers() {
        constexpr size_t VECTOR_SIZE = 100;
        const int TOTAL_ACTIONS_NUMBER = 100;
        utils::RandomDataGenerator generator(VECTOR_SIZE, 0, INT_MAX, 0.1);
        std::vector<int> input_data = generator.GenerateRandomVector();

        utils::RSQConsistencyChecker<T> checker(input_data);
        for (int i = 0; i < TOTAL_ACTIONS_NUMBER; ++i) {
            std::size_t index_to_update = generator.GetRandomIndex();
            int new_value = generator.GetRandomInt();
            checker.CheckQuery(0, VECTOR_SIZE - 1);
            checker.SimpleCheckUpdate(index_to_update, new_value);
            if (generator.CheckChangeAction()) {
                checker.FullCheck();  // проверяем, что все суммы корректны
            }
        }
        checker.FullCheck();
    }

    // проверяем корректность на небольшом векторе с большими позитивными
    // числами
    void TestBigNegativeNumbers() {
        constexpr size_t VECTOR_SIZE = 100;
        const int TOTAL_ACTIONS_NUMBER = 100;
        utils::RandomDataGenerator generator(VECTOR_SIZE, INT_MIN, 0, 0.1);
        std::vector<int> input_data = generator.GenerateRandomVector();

        utils::RSQConsistencyChecker<T> checker(input_data);
        for (int i = 0; i < TOTAL_ACTIONS_NUMBER; ++i) {
            std::size_t index_to_update = generator.GetRandomIndex();
            int new_value = generator.GetRandomInt();
            checker.CheckQuery(0, VECTOR_SIZE - 1);
            checker.SimpleCheckUpdate(index_to_update, new_value);
            if (generator.CheckChangeAction()) {
                checker.FullCheck();
            }
        }
        checker.FullCheck();
    }
};

}  // namespace rsq::tests

#endif