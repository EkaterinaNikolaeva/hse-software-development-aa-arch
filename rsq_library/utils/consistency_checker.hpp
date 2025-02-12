#ifndef RSQ_CONSISTENCY_CHECKER_HPP
#define RSQ_CONSISTENCY_CHECKER_HPP

#include <irsq.hpp>
#include <naive.hpp>
#include <vector>

namespace rsq::utils {

template <typename T>
class RSQConsistencyChecker {
 private:
  NaiveRSQ naive_rsq;
  T custom_rsq;

 public:
  explicit RSQConsistencyChecker(const std::vector<int>& input)
      : naive_rsq(input), custom_rsq(input) {}

  int CheckQuery(std::size_t left, std::size_t right) {
    int naive_sum = naive_rsq.Query(left, right);
    int custom_sum = custom_rsq.Query(left, right);
    EXPECT_EQ(naive_sum, custom_sum);
    return naive_sum;
  }

  void Update(std::size_t index, int value) {
    naive_rsq.Update(index, value);
    custom_rsq.Update(index, value);
  }

  void SimpleCheckUpdate(std::size_t index, int value) {
    naive_rsq.Update(index, value);
    custom_rsq.Update(index, value);
    CheckQuery(index, index);
  }

  void FullCheck() {
    for (int l = 0; l < naive_rsq.size(); ++l) {
      for (int r = l; r < naive_rsq.size(); ++r) {
        CheckQuery(l, r);
      }
    }
  }
};

}  // namespace rsq::utils

#endif  // RSQ_CONSISTENCY_CHECKER_HPP