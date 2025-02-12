#include <gtest/gtest.h>
#include <irsq_better_test.hpp>
#include <irsq.hpp>
#include <irsq_random_test.hpp>
#include <irsq_test.hpp>
#include <naive.hpp>
#include <segment_tree.hpp>
#include <sqrt_rsq.hpp>

using SegmentTreeTest = rsq::tests::IRSQTest<rsq::SegmentTree>;
using SegmentTreeBetterTest = rsq::tests::IRSQBetterTest<rsq::SegmentTree>;
using SegmentTreeRandomTest = rsq::tests::RandomIRSQTest<rsq::SegmentTree>;
using NaiveTest = rsq::tests::IRSQTest<rsq::NaiveRSQ>;
using SqrtRSQTest = rsq::tests::IRSQTest<rsq::SqrtRSQ>;
using SqrtRSQRandmomTest = rsq::tests::RandomIRSQTest<rsq::SqrtRSQ>;
using FenwickTest = rsq::tests::IRSQTest<rsq::SqrtRSQ>;
using FenwickRandmomTest = rsq::tests::RandomIRSQTest<rsq::SqrtRSQ>;

TEST_F(SegmentTreeTest, BasicOperationsSegmentTree) {
    SimpleTestIRSQ();
}

TEST_F(NaiveTest, BasicOperationsNaive) {
    SimpleTestIRSQ();
}

TEST_F(SegmentTreeBetterTest, BetterOperationsSegmentTree) {
    TestBigVectorSize();
    TestBigPositiveNumbers();
    TestBigNegativeNumbers();
}

TEST_F(SegmentTreeRandomTest, RandomOperationsSegmentTree) {
    RandomActionsTest();
    RandomActionsTest(0.1);                 // 1 update : 9 query
    RandomActionsTest(0.9);                 // 9 update : 1 query
    RandomActionsTest(0.01);                // 1 update : 99 query
    RandomActionsTest(0.99);                // 99 update : 1 query
    RandomActionsTest(0);                   // query only
    RandomActionsTest(1);                   // update only
    RandomActionsTest(0.5, 10000000, 100);  // small vector
}

TEST_F(SegmentTreeTest, BasicOperations) {
    SimpleTestIRSQ();
}

TEST_F(SegmentTreeRandomTest, RandomOperations) {
    RandomActionsTest();
}

TEST_F(SqrtRSQTest, BasicOperations) {
    SimpleTestIRSQ();
}

TEST_F(SqrtRSQRandmomTest, RandomOperations) {
    RandomActionsTest();
}

TEST_F(FenwickTest, BasicOperations) {
    SimpleTestIRSQ();
}

TEST_F(FenwickRandmomTest, RandomOperations) {
    RandomActionsTest();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
