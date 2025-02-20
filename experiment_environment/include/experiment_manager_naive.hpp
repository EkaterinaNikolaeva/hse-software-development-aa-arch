#ifndef EXPERIMENT_MANAGER_NAIVE_HPP
#define EXPERIMENT_MANAGER_NAIVE_HPP

#include <iostream>
#include <naive.hpp>
#include <segment_tree.hpp>
#include <fenwick_tree.hpp>
#include <down_segment_tree.hpp>
#include <treap.hpp>
#include <vector>
#include "benchmark.hpp"
#include "experiment_manager_base.hpp"

namespace rsq::benchmark {
class ExperimentManagerNaive : public ExperimentManagerBase {
private:
    template <typename RSQType>
    void RunExperiment(const std::string &experiment_name, std::size_t size)
        const {
        std::cerr << "Naive" << ',' << experiment_name << ',' << size << ','
                  << Benchmark::Measure(MakeNaiveActions<RSQType>, size)
                  << "\n";
        std::cerr << "Random" << ',' << experiment_name << ',' << size << ','
                  << Benchmark::Measure(MakeRandomActions<RSQType>, size)
                  << "\n";
        std::cerr << "Random_Update" << ',' << experiment_name << ',' << size
                  << ','
                  << Benchmark::Measure(
                         MakeBenchmarkRandomParameterizedTest<RSQType>, size,
                         -100, 100, 0.99
                     )
                  << "\n";
        std::cerr << "Random_Query" << ',' << experiment_name << ',' << size
                  << ','
                  << Benchmark::Measure(
                         MakeBenchmarkRandomParameterizedTest<RSQType>, size,
                         -100, 100, 0.01
                     )
                  << "\n";
        std::cerr << "Constructor" << ',' << experiment_name << ',' << size
                  << ',' << Benchmark::Measure(MakeConstructor<RSQType>, size)
                  << "\n";
    }

public:
    explicit ExperimentManagerNaive(const std::vector<int> &sizes)
        : ExperimentManagerBase(sizes) {
        std::cerr << "Benchmark_name,Algorithm_name,Size_of_structure,Time("
                     "microseconds),Memory(KB)\n";
    }

    void RunExperiments() override {
        for (std::size_t size : random_sizes_) {
            RunExperiment<NaiveRSQ>("NaiveRSQ", size);
            RunExperiment<SegmentTree>("SegmentTree", size);
            RunExperiment<SqrtRSQ>("SqrtRSQ", size);
            RunExperiment<FenwickTree>("FenwickTree", size);
            RunExperiment<DownSegmentTree>("DownSegmentTree", size);
            RunExperiment<Treap>("Treap", size);
        }
    }
};

}  // namespace rsq::benchmark

#endif  // EXPERIMENT_MANAGER_NAIVE_HPP
