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
  void RandomActionsTest(const double update_probability = 0.5,
                         const size_t total_actions_number = 1000000,
                         const size_t vector_size = 1000,
                         const int min_element = -100,
                         const int max_element = 100) {
    utils::RandomDataGenerator generator = utils::RandomDataGenerator(
        vector_size, min_element, max_element, update_probability);
    std::vector<int> input_data = generator.GenerateRandomVector();
    utils::RSQConsistencyChecker<T> checker(input_data);

    for (int action = 0; action < total_actions_number; ++action) {
      if (generator.CheckChangeAction()) {
        std::size_t random_index = generator.GetRandomIndex();
        int random_value = generator.GetRandomInt();
        checker.SimpleCheckUpdate(random_index, random_value);
      } else {
        std::size_t left = generator.GetRandomIndex();
        std::size_t right = generator.GetRandomIndex();
        if (left > right) std::swap(left, right);
        checker.CheckQuery(left, right);
      }
    }
  }
};

}  // namespace rsq::tests
#endif