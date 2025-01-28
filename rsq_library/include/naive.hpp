#ifndef NAIVE_HPP
#define NAIVE_HPP

#include <irsq.hpp>
#include <vector>

namespace rsq {

class NaiveRSQ : public IRSQ {
 private:
  std::vector<int> data;

 public:
  explicit NaiveRSQ(const std::vector<int>& input) : IRSQ(input), data(input) {}

  void Update(std::size_t index, int value) override {
    if (index >= data.size()) {
      throw RSQOutOfBoundsError();
    }
    data[index] = value;
  }

  int Query(std::size_t left, std::size_t right) override {
    if (left > right || left >= data.size() || right >= data.size()) {
      throw RSQOutOfBoundsError();
    }
    int sum = 0;
    for (std::size_t i = left; i <= right; ++i) {
      sum += data[i];
    }
    return sum;
  }
};

}  // namespace rsq

#endif  // NAIVE_HPP
