#ifndef EXPERIMENT_MANAGER_NAIVE_HPP
#define EXPERIMENT_MANAGER_NAIVE_HPP

#include <down_segment_tree.hpp>
#include <fenwick_tree.hpp>
#include <iostream>
#include <naive.hpp>
#include <segment_tree.hpp>
#include <prefix_sum.hpp>
#include <lazy_prefix_sum.hpp>
#include <sharded_prefix_sum.hpp>
#include <sharded_lazy_prefix_sum.hpp>
#include <prefix_sum.hpp>
#include <vector>
#include "benchmark.hpp"
#include "experiment_manager_base.hpp"

namespace rsq::benchmark {

// Менеджер использует самописную библиотеку для бенчмаркинга
class ExperimentManagerNaive : public ExperimentManagerBase {
private:
    // передаем в Benchmark::MeasureTime метод, время работы которого измеряем и
    // параметры
    template <typename RSQType>
    void RunExperiment(const std::string &experiment_name, std::size_t size)
        const {
        std::cerr << "Naive," << size << ',' << experiment_name << ','
                  << Benchmark::MeasureTime(MakeNaiveActions<RSQType>, size)
                  << "\n";
        std::cerr << "Random," << size << ',' << experiment_name << ','
                  << Benchmark::MeasureTime(MakeRandomActions<RSQType>, size)
                  << "\n";
        std::cerr << "Random_Update," << size << ',' << experiment_name << ','
                  << Benchmark::MeasureTime(
                         MakeBenchmarkRandomParameterizedTest<RSQType>, size,
                         -100, 100, 0.99
                     )
                  << "\n";
        std::cerr << "Random_Query," << size << ',' << experiment_name << ','
                  << Benchmark::MeasureTime(
                         MakeBenchmarkRandomParameterizedTest<RSQType>, size,
                         -100, 100, 0.01
                     )
                  << "\n";
        std::cerr << "Constructor," << size << ',' << experiment_name << ','
                  << Benchmark::MeasureTime(MakeConstructor<RSQType>, size)
                  << "\n";
    }

public:
    explicit ExperimentManagerNaive(const std::vector<int> &sizes)
        : ExperimentManagerBase(sizes) {
    }

    void RunExperiments() override {
        for (std::size_t size : random_sizes_) {
            RunExperiment<NaiveRSQ>("NaiveRSQ", size);
            RunExperiment<SegmentTree>("SegmentTree", size);
            RunExperiment<SqrtRSQ>("SqrtRSQ", size);
            RunExperiment<FenwickTree>("Fenwick", size);
            RunExperiment<DownSegmentTree>("DownSegmentTree", size);
            RunExperiment<PrefixSum>("PrefixSum", size);
            RunExperiment<LazyPrefixSum>("LazyPrefixSum", size);
            RunExperiment<ShardedPrefixSum>("ShardedPrefixSum", size);
            RunExperiment<ShardedLazyPrefixSum>("ShardedLazyPrefixSum", size);
        }
    }
};

}  // namespace rsq::benchmark

#endif  // EXPERIMENT_MANAGER_NAIVE_HPP
