#ifndef IRSQ_RANDOM_TEST_HPP
#define IRSQ_RANDOM_TEST_HPP

#include <gtest/gtest.h>

#include <ctime>
#include <irsq.hpp>
#include <naive.hpp>
#include <random>
#include <random_data_generator.hpp>
#include <segment_tree.hpp>

namespace rsq::tests {

template <typename T>
class RandomIRSQTest : public ::testing::Test {
 private:
  const int VECTOR_SIZE = 1000;
  const int TOTAL_ACTIONS_NUMBER = 1000000;
  utils::RandomDataGenerator generator;

 protected:
  void RandomActionsTest() {
    std::vector<int> input_data = generator.GenerateRandomVector(VECTOR_SIZE);
    auto algo_rsq = T(input_data);
    auto naive_rsq = NaiveRSQ(input_data);

    for (int action = 0; action < TOTAL_ACTIONS_NUMBER; ++action) {
      if (generator.CheckChangeAction()) {
        std::size_t random_index = generator.GetRandomIndex(VECTOR_SIZE);
        std::size_t random_value = generator.GetRandomInt();
        algo_rsq.Update(random_index, random_value);
        naive_rsq.Update(random_index, random_value);
      } else {
        std::size_t left = generator.GetRandomIndex(VECTOR_SIZE);
        std::size_t right = generator.GetRandomIndex(VECTOR_SIZE);
        if (left > right) std::swap(left, right);
        EXPECT_EQ(algo_rsq.Query(left, right), naive_rsq.Query(left, right));
      }
    }
  }
};

}  // namespace rsq::tests
#endif