#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <functional>
#include <iostream>
#include <atomic>

std::atomic<unsigned long long> allocatedMemory(0);

void *operator new(size_t size) {
    allocatedMemory.fetch_add(size);
    return std::malloc(size);
}

namespace rsq::benchmark {

struct BenchmarkResult {
    int64_t time;
    double memory;
};

class Benchmark {
public:
    template <typename F, typename... Args>
    static BenchmarkResult MeasureTime(F func, Args &&...args) {
        auto memBefore = allocatedMemory.load();
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        auto memAfter = allocatedMemory.load();

        auto time =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count();
        auto memUsed = (memAfter - memBefore) / 1024.0;

        return {time, memUsed};
    }
};

}  // namespace rsq::benchmark

#endif  // BENCHMARK_HPP
