#ifndef EXPERIMENT_MANAGER_GOOGLE_HPP
#define EXPERIMENT_MANAGER_GOOGLE_HPP

#include <benchmark/benchmark.h>
#include <down_segment_tree.hpp>
#include <fenwick_tree.hpp>
#include <functional>
#include <naive.hpp>
#include <segment_tree.hpp>
#include <sqrt_rsq.hpp>
#include "experiment_manager_base.hpp"

namespace rsq::benchmark {

// Менеджер использует google benchmark
class ExperimentManagerGoogle : public ExperimentManagerBase {
private:
    template <typename RSQType>
    void RegisterType(std::size_t size, const std::string &class_name) {
        ::benchmark::
            RegisterBenchmark(("BM_Naive_RSQ" + class_name).c_str(), RunNaiveActions<RSQType>)
                ->Arg(size);
        ::benchmark::
            RegisterBenchmark(("BM_Random_RSQ" + class_name).c_str(), RunRandomActions<RSQType>)
                ->Arg(size);
        ::benchmark::RegisterBenchmark(
            ("BM_Random_Update_RSQ" + class_name).c_str(),
            std::bind(
                RunRandomActionsParameterized<RSQType>, -100, 100, 0.99,
                std::placeholders::_1
            )
        )
            ->Arg(size);
        ::benchmark::RegisterBenchmark(
            ("BM_Random_Query_RSQ" + class_name).c_str(),
            std::bind(
                RunRandomActionsParameterized<RSQType>, -100, 100, 0.01,
                std::placeholders::_1
            )
        )
            ->Arg(size);
    }

public:
    explicit ExperimentManagerGoogle(const std::vector<int> &sizes)
        : ExperimentManagerBase(sizes) {
    }

    template <typename RSQType>
    static void RunNaiveActions(::benchmark::State &state) {
        std::size_t size = state.range(0);
        for (auto _ : state) {
            MakeNaiveActions<RSQType>(size
            );  // вызываем метод, определенный в базовом классе, google
                // benchmark посчитает за нас
        }
    }

    template <typename RSQType>
    static void RunRandomActions(::benchmark::State &state) {
        size_t size = state.range(0);
        for (auto _ : state) {
            MakeRandomActions<RSQType>(size
            );  // вызываем метод, определенный в базовом классе, google
                // benchmark посчитает за нас
        }
    }

    template <typename RSQType>
    static void RunRandomActionsParameterized(
        int min_element,
        int max_element,
        double update_probability,
        ::benchmark::State &state
    ) {
        size_t size = state.range(0);
        for (auto _ : state) {
            MakeBenchmarkRandomParameterizedTest<RSQType>(
                size, min_element, max_element, update_probability
            );  // вызываем метод, определенный в базовом классе, google
                // benchmark посчитает за нас
        }
    }

    void RunExperiments() override {
        for (std::size_t size : random_sizes_) {
            // RegisterType<NaiveRSQ>(size, "Naive");
            RegisterType<SegmentTree>(size, "SegmentTree");
            RegisterType<SqrtRSQ>(size, "Sqrt");
            RegisterType<FenwickTree>(size, "Fenwick");
            RegisterType<DownSegmentTree>(size, "DownSegmentTree");
        }

        ::benchmark::RunSpecifiedBenchmarks();
    }
};

}  // namespace rsq::benchmark
#endif  // EXPERIMENT_MANAGER_GOOGLE_HPP
