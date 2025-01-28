#ifndef IRSQ_TEST_HPP
#define IRSQ_TEST_HPP

#include <gtest/gtest.h>

#include <irsq.hpp>
#include <naive.hpp>
#include <segment_tree.hpp>

namespace rsq::tests {

template <typename T>
class IRSQTest : public ::testing::Test {
 protected:
  std::vector<int> input_data;

  void SetUp() override { input_data = {1, 3, 5, 7, 9, 11}; }

  std::unique_ptr<T> CreateRSQInstance() {
    return std::make_unique<T>(input_data);
  }

  void SimpleTestIRSQ() {
    {
      auto rsq = CreateRSQInstance();
      EXPECT_NO_THROW(rsq->Query(0, 5));
    }
    {
      auto rsq = CreateRSQInstance();

      EXPECT_EQ(rsq->Query(0, 5), 36);
      EXPECT_EQ(rsq->Query(1, 3), 15);

      EXPECT_THROW(rsq->Query(0, 6), RSQOutOfBoundsError);
    }
    {
      auto rsq = CreateRSQInstance();

      rsq->Update(0, 10);
      EXPECT_EQ(rsq->Query(0, 5), 45);

      rsq->Update(0, -1);
      EXPECT_EQ(rsq->Query(0, 5), 34);

      EXPECT_THROW(rsq->Update(6, 5), RSQOutOfBoundsError);
    }
  }
};

}  // namespace rsq::tests
#endif  // IRSQ_TEST_HPP
