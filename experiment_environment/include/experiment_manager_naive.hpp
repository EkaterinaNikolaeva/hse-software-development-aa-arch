#ifndef EXPERIMENT_MANAGER_NAIVE_HPP
#define EXPERIMENT_MANAGER_NAIVE_HPP

#include <down_segment_tree.hpp>
#include <fenwick_tree.hpp>
#include <iostream>
#include <naive.hpp>
#include <segment_tree.hpp>
#include <string>
#include <vector>
#include "benchmark.hpp"
#include "experiment_manager_base.hpp"

namespace rsq::benchmark {
class ExperimentManagerNaive : public ExperimentManagerBase {
private:
    template <typename RSQType>
    void RunExperiment(const std::string &experiment_name, std::size_t size)
        const {
        Benchmark::Measure(
            experiment_name + "_Naive/" + std::to_string(size) + "_",
            MakeNaiveActions<RSQType>, size
        );
        Benchmark::Measure(
            experiment_name + "_Random/" + std::to_string(size) + "_",
            MakeRandomActions<RSQType>, size
        );
        Benchmark::Measure(
            experiment_name + "_Random_Update/" + std::to_string(size) + "_",
            MakeBenchmarkRandomParameterizedTest<RSQType>, size, -100, 100, 0.99
        );
        Benchmark::Measure(
            experiment_name + "_Random_Query/" + std::to_string(size) + "_",
            MakeBenchmarkRandomParameterizedTest<RSQType>, size, -100, 100, 0.01
        );
    }

public:
    explicit ExperimentManagerNaive(const std::vector<int> &sizes)
        : ExperimentManagerBase(sizes) {
    }

    void RunExperiments() override {
        for (std::size_t size : random_sizes_) {
            RunExperiment<SegmentTree>("SegmentTree", size);
            // RunExperiment<NaiveRSQ>("NaiveRSQ", size);
            RunExperiment<SqrtRSQ>("SqrtRSQ", size);
            RunExperiment<FenwickTree>("Fenwick", size);
            RunExperiment<DownSegmentTree>("DownSegmentTree", size);
        }
    }
};

}  // namespace rsq::benchmark

#endif  // EXPERIMENT_MANAGER_NAIVE_HPP
