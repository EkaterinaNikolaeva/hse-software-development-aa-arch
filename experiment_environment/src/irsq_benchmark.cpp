#include <benchmark/benchmark.h>
#include <naive.hpp>
#include <segment_tree.hpp>
#include <vector>
#include "config_loader.hpp"
#include "random_data_generator.hpp"

namespace rsq {

class ExperimentManager {
private:
    std::vector<int> random_sizes;

public:
    explicit ExperimentManager(std::vector<int> sizes)
        : random_sizes(std::move(sizes)) {
    }

    template <typename RSQType>
    static void benchmark_naive_test(benchmark::State &state) {
        const size_t size = state.range(0);
        for (auto _ : state) {
            std::vector<int> data(size, 1);
            RSQType rsq(data);
            for (size_t i = 0; i < size; ++i) {
                rsq.Update(i, i);
                rsq.Query(0, size - 1);
            }
        }
    }

    template <typename RSQType>
    static void benchmark_random_test(benchmark::State &state) {
        const size_t size = state.range(0);
        rsq::utils::RandomDataGenerator generator(size);

        for (auto _ : state) {
            std::vector<int> data = generator.GenerateRandomVector();
            RSQType rsq(data);
            for (size_t i = 0; i < size; ++i) {
                rsq.Update(
                    generator.GetRandomIndex(), generator.GetRandomInt()
                );
                std::size_t left = generator.GetRandomIndex();
                std::size_t right = generator.GetRandomIndex();
                if (left > right)
                    std::swap(left, right);
                rsq.Query(left, right);
            }
        }
    }

    template <typename RSQType>
    static void benchmark_random_test_with_parameters(
        int min_element,
        int max_element,
        double update_probability,
        benchmark::State &state
    ) {
        const size_t size = state.range(0);

        rsq::utils::RandomDataGenerator generator(
            size, min_element, max_element, update_probability
        );
        for (auto _ : state) {
            std::vector<int> data = generator.GenerateRandomVector();
            RSQType rsq(data);
            for (size_t i = 0; i < 2 * size; ++i) {
                if (generator.CheckChangeAction()) {
                    rsq.Update(
                        generator.GetRandomIndex(), generator.GetRandomInt()
                    );
                } else {
                    std::size_t left = generator.GetRandomIndex();
                    std::size_t right = generator.GetRandomIndex();
                    if (left > right)
                        std::swap(left, right);
                    rsq.Query(left, right);
                }
            }
        }
    }

    void runExperiments() const {
        for (int size : random_sizes) {
            benchmark::
                RegisterBenchmark("BM_Naive_RSQNaive", benchmark_naive_test<NaiveRSQ>)
                    ->Arg(size);
            benchmark::
                RegisterBenchmark("BM_Naive_RSQSegmentTree", benchmark_naive_test<SegmentTree>)
                    ->Arg(size);

            benchmark::
                RegisterBenchmark("BM_Random_RSQNaive", benchmark_random_test<NaiveRSQ>)
                    ->Arg(size);
            benchmark::
                RegisterBenchmark("BM_Random_RSQSegmentTree", benchmark_random_test<SegmentTree>)
                    ->Arg(size);
            benchmark::RegisterBenchmark(
                "BM_Random_Update_RSQNaive",
                std::bind(
                    benchmark_random_test_with_parameters<NaiveRSQ>, -100, 100,
                    0.99, std::placeholders::_1
                )
            )
                ->Arg(size);
            benchmark::RegisterBenchmark(
                "BM_Random_Query_RSQNaive",
                std::bind(
                    benchmark_random_test_with_parameters<NaiveRSQ>, -100, 100,
                    0.01, std::placeholders::_1
                )
            )
                ->Arg(size);
            benchmark::RegisterBenchmark(
                "BM_Random_Update_RSQSegmentTree",
                std::bind(
                    benchmark_random_test_with_parameters<SegmentTree>, -100,
                    100, 0.99, std::placeholders::_1
                )
            )
                ->Arg(size);
            benchmark::RegisterBenchmark(
                "BM_Random_Query_RSQSegmentTree",
                std::bind(
                    benchmark_random_test_with_parameters<SegmentTree>, -100,
                    100, 0.01, std::placeholders::_1
                )
            )
                ->Arg(size);
        }

        benchmark::RunSpecifiedBenchmarks();
    }
};

}  // namespace rsq

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            throw std::runtime_error(
                "Error: Missing config file argument.\nUsage: ./benchmark "
                "<config.json>"
            );
        }

        std::string config_filename = argv[1];
        std::vector<int> test_sizes = ConfigLoader::loadConfig(config_filename);

        rsq::ExperimentManager experimentManager(test_sizes);
        experimentManager.runExperiments();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
