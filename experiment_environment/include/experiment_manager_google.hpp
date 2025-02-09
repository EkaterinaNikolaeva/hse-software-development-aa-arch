#ifndef EXPERIMENT_MANAGER_GOOGLE_HPP
#define EXPERIMENT_MANAGER_GOOGLE_HPP

#include <benchmark/benchmark.h>

#include <naive.hpp>
#include <segment_tree.hpp>

#include "experiment_manager_base.hpp"

namespace rsq::benchmark {

class ExperimentManagerGoogle : public ExperimentManagerBase {
 private:
  template <typename RSQType>
  void RegisterType(std::size_t size) {
    ::benchmark::RegisterBenchmark("BM_Naive_RSQNaive",
                                   RunNaiveActions<RSQType>)
        ->Arg(size);
    ::benchmark::RegisterBenchmark("BM_Random_RSQSegmentTree",
                                   RunRandomActions<RSQType>)
        ->Arg(size);
  }

 public:
  explicit ExperimentManagerGoogle(const std::vector<int> &sizes)
      : ExperimentManagerBase(sizes) {}

  template <typename RSQType>
  static void RunNaiveActions(::benchmark::State &state) {
    std::size_t size = state.range(0);
    for (auto _ : state) {
      MakeNaiveActions<RSQType>(size);
    }
  }

  template <typename RSQType>
  static void RunRandomActions(::benchmark::State &state) {
    size_t size = state.range(0);
    for (auto _ : state) {
      MakeRandomActions<RSQType>(size);
    }
  }

  void RunExperiments() override {
    for (std::size_t size : random_sizes_) {
      RegisterType<NaiveRSQ>(size);
      RegisterType<SegmentTree>(size);
    }

    ::benchmark::RunSpecifiedBenchmarks();
  }
};

}  // namespace rsq::benchmark
#endif  // EXPERIMENT_MANAGER_GOOGLE_HPP
