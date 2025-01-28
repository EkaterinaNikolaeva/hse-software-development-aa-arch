#include <benchmark/benchmark.h>
#include <vector>
#include <naive.hpp>
#include <segment_tree.hpp>

namespace rsq {

    class ExperimentManager {
    private:
        int startRange;
        int endRange;
        int step;

    public:
        ExperimentManager(int start_range, int end_range, int step_size)
                : startRange(start_range), endRange(end_range), step(step_size) {}

        template <typename RSQType>
        static void benchmark_test(benchmark::State& state) {
            size_t size = state.range(0);
            std::vector<int> data(size, 1);

            RSQType rsq(data);
            for (auto _ : state) {
                for (size_t i = 0; i < size; ++i) {
                    rsq.Update(i, i);
                    rsq.Query(0, size - 1);
                }
            }
        }

        void runExperiments() const {
                BENCHMARK_TEMPLATE(benchmark_test, NaiveRSQ)->RangeMultiplier(step)->Range(startRange, endRange);
                BENCHMARK_TEMPLATE(benchmark_test, SegmentTree)->RangeMultiplier(step)->Range(startRange, endRange);
            benchmark::RunSpecifiedBenchmarks();
        }
    };

}

int main() {
    rsq::ExperimentManager experimentManager(100, 100000, 100);
    experimentManager.runExperiments();

    return 0;
}
