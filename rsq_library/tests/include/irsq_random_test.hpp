#ifndef IRSQ_RANDOM_TEST_HPP
#define IRSQ_RANDOM_TEST_HPP

#include <gtest/gtest.h>

#include <ctime>
#include <irsq.hpp>
#include <naive.hpp>
#include <random>
#include <segment_tree.hpp>

namespace rsq::tests {

std::mt19937 rng(std::time(0));

template <typename T>
class RandomIRSQTest : public ::testing::Test {
 private:
  const int ABS_MAX_ELEMENT_ = 100;
  const int VECTOR_SIZE = 1000;
  const int TOTAL_ACTIONS_NUMBER = 1000000;
  const double PROBABILITY_CHANGE = 0.3;

  int GetRandomInt() {
    return rng() % (2 * ABS_MAX_ELEMENT_) - ABS_MAX_ELEMENT_;
  }

  std::size_t GetRandomIndex() {
    return static_cast<std::size_t>(rng() % VECTOR_SIZE);
  }

  bool CheckChangeAction() {
    return rng() % ABS_MAX_ELEMENT_ < PROBABILITY_CHANGE * ABS_MAX_ELEMENT_;
  }

  std::vector<int> GenerateRandomVector(std::size_t vector_size) {
    std::vector<int> result(vector_size);
    for (std::size_t i = 0; i < vector_size; ++i) {
      result[i] = GetRandomInt();
    }
    return result;
  }

 protected:
  void RandomActionsTest() {
    std::vector<int> input_data = GenerateRandomVector(VECTOR_SIZE);
    auto algo_rsq = T(input_data);
    auto naive_rsq = NaiveRSQ(input_data);
    for (int action = 0; action < TOTAL_ACTIONS_NUMBER; ++action) {
      if (CheckChangeAction()) {
        std::size_t random_index = GetRandomIndex();
        std::size_t random_value = GetRandomInt();
        algo_rsq.Update(random_index, random_value);
        naive_rsq.Update(random_index, random_value);
      } else {
        std::size_t left = GetRandomIndex();
        std::size_t right = GetRandomIndex();
        if (left > right) {
          std::swap(left, right);
        }
        EXPECT_EQ(algo_rsq.Query(left, right), naive_rsq.Query(left, right));
      }
    }
  }
};

}  // namespace rsq::tests

#endif  // IRSQ_RANDOM_TEST_HPP
