#ifndef IRSQ_RANDOM_TEST_HPP
#define IRSQ_RANDOM_TEST_HPP

#include <gtest/gtest.h>
#include <consistency_checker.hpp>
#include <ctime>
#include <irsq.hpp>
#include <naive.hpp>
#include <random>
#include <random_data_generator.hpp>
#include <segment_tree.hpp>

namespace rsq::tests {

template <typename T>
class RandomIRSQTest : public ::testing::Test {
protected:
    void RandomActionsTest(
        double update_probability =
            0.5,  // вероятность совершения запроса изменения элемента
        size_t total_actions_number = 1'000'000,  // общее количество действий
        size_t vector_size = 1'000,  // размер массива
        int min_element = -100,  // минимальное значение элемента в массиве
        int max_element = 100  // максимальное значение элемента в массиве
    ) {
        utils::RandomDataGenerator generator(
            vector_size, min_element, max_element, update_probability
        );
        auto input_data = generator.GenerateRandomVector();
        utils::RSQConsistencyChecker<T> checker(input_data);

        for (size_t action = 0; action < total_actions_number; ++action) {
            if (generator.CheckChangeAction(
                )) {  // проверяем, какого типа текущее действие
                checker.SimpleCheckUpdate(
                    generator.GetRandomIndex(), generator.GetRandomInt()
                );
            } else {
                size_t left = generator.GetRandomIndex();
                size_t right = generator.GetRandomIndex();
                if (left > right)
                    std::swap(left, right);
                checker.CheckQuery(left, right);
            }
        }
    }
};

}  // namespace rsq::tests

#endif
