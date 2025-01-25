#ifndef IRSQ_HPP
#define IRSQ_HPP

#include <cstddef>
#include <stdexcept>

namespace rsq {

struct RSQOutOfBoundsError : std::runtime_error {
  RSQOutOfBoundsError() : std::runtime_error("Incorrect query bounds") {}
};

struct IRSQ {
  virtual int Query(std::size_t left, std::size_t right) = 0;
  virtual void Update(std::size_t index, int value) = 0;
  virtual ~IRSQ() = default;
};

}  // namespace rsq

#endif  // IRSQ_HPP