#ifndef IRSQ_HPP
#define IRSQ_HPP

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace rsq {

struct RSQOutOfBoundsError : public std::runtime_error {
  RSQOutOfBoundsError() : std::runtime_error("Incorrect query bounds") {}
};

class IRSQ {
 protected:
  const std::size_t INPUT_ARRAY_LENGTH_;

  void CheckIndex(std::size_t index) {
    if (index >= INPUT_ARRAY_LENGTH_) {
      throw RSQOutOfBoundsError();
    }
  }

  void CheckRange(std::size_t left, std::size_t right) {
    if (left > right || left >= INPUT_ARRAY_LENGTH_ ||
        right >= INPUT_ARRAY_LENGTH_) {
      throw RSQOutOfBoundsError();
    }
  }

 public:
  explicit IRSQ(const std::vector<int> &input)
      : INPUT_ARRAY_LENGTH_(input.size()) {}

  virtual int Query(std::size_t left, std::size_t right) = 0;
  virtual void Update(std::size_t index, int value) = 0;
  virtual ~IRSQ() = default;
};

}  // namespace rsq

#endif  // IRSQ_HPP