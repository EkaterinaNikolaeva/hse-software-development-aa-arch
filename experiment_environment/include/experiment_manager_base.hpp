#ifndef EXPERIMENT_MANAGER_BASE_HPP
#define EXPERIMENT_MANAGER_BASE_HPP

#include <random_data_generator.hpp>
#include <vector>

namespace rsq::benchmark {

class ExperimentManagerBase {
 protected:
  std::vector<int> random_sizes_;

  template <typename RSQType>
  static void MakeNaiveActions(std::size_t size) {
    std::vector<int> data(size, 1);
    RSQType rsq(data);
    for (size_t i = 0; i < size; ++i) {
      rsq.Update(i, i);
      rsq.Query(0, size - 1);
    }
  }

  template <typename RSQType>
  static void MakeRandomActions(std::size_t size) {
    rsq::utils::RandomDataGenerator generator;
    std::vector<int> data = generator.GenerateRandomVector(size);

    RSQType rsq(data);
    for (size_t i = 0; i < size; ++i) {
      rsq.Update(generator.GetRandomIndex(size), generator.GetRandomInt());
      std::size_t left = generator.GetRandomIndex(size);
      std::size_t right = generator.GetRandomIndex(size);
      if (left > right) std::swap(left, right);
      rsq.Query(left, right);
    }
  }

 public:
  explicit ExperimentManagerBase(std::vector<int> sizes)
      : random_sizes_(std::move(sizes)) {}

  virtual void RunExperiments() = 0;

  virtual ~ExperimentManagerBase() = default;
};

}  // namespace rsq::benchmark

#endif  // EXPERIMENT_MANAGER_BASE_HPP