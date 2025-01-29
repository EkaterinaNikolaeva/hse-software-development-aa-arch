#include <gtest/gtest.h>

#include <irsq_random_test.hpp>
#include <irsq_test.hpp>

using SegmentTreeTest = rsq::tests::IRSQTest<rsq::SegmentTree>;
using SegmentTreeRandomTest = rsq::tests::RandomIRSQTest<rsq::SegmentTree>;
using NaiveTest = rsq::tests::IRSQTest<rsq::NaiveRSQ>;

TEST_F(SegmentTreeTest, BasicOperationsSegmentTree) { SimpleTestIRSQ(); }

TEST_F(NaiveTest, BasicOperationsNaive) { SimpleTestIRSQ(); }

TEST_F(SegmentTreeRandomTest, RandomOperationsSegmentTree) {
  RandomActionsTest();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
