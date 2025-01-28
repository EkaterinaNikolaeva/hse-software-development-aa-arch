#include <benchmark/benchmark.h>

#include <irsq.hpp>
#include <naive.hpp>
#include <segment_tree.hpp>

template <typename RSQType>
static void benchmark_test(benchmark::State &state) {
  for (auto _ : state) {
    int size = 1000;
    int sum = 0;
    std::vector<int> vec(size, 0);
    RSQType rsq(vec);
    for (std::size_t i = 0; i < size; ++i) {
      rsq.Update(i, i);
      sum += i;
      assert(sum == rsq.Query(0, size - 1));
    }
  }
}
BENCHMARK_TEMPLATE(benchmark_test, rsq::SegmentTree);
BENCHMARK_TEMPLATE(benchmark_test, rsq::Naive);

BENCHMARK_MAIN();