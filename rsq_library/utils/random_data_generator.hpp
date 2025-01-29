#ifndef RSQ_RANDOM_DATA_GENERATOR_HPP
#define RSQ_RANDOM_DATA_GENERATOR_HPP

#include <ctime>
#include <random>
#include <vector>

namespace rsq::utils {

class RandomDataGenerator {
 private:
  std::mt19937 rng;
  const int ABS_MAX_ELEMENT;

 public:
  explicit RandomDataGenerator(int abs_max_element = 100)
      : rng(std::time(nullptr)), ABS_MAX_ELEMENT(abs_max_element) {}

  int GetRandomInt() { return rng() % (2 * ABS_MAX_ELEMENT) - ABS_MAX_ELEMENT; }

  std::size_t GetRandomIndex(std::size_t vector_size) {
    return static_cast<std::size_t>(rng() % vector_size);
  }

  bool CheckChangeAction(double probability = 0.3) {
    return rng() % ABS_MAX_ELEMENT < probability * ABS_MAX_ELEMENT;
  }

  std::vector<int> GenerateRandomVector(std::size_t vector_size) {
    std::vector<int> result(vector_size);
    for (std::size_t i = 0; i < vector_size; ++i) {
      result[i] = GetRandomInt();
    }
    return result;
  }
};

}  // namespace rsq::utils

#endif  // RSQ_RANDOM_DATA_GENERATOR_HPP
