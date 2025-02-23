#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <functional>

namespace rsq::benchmark {

// Библиотека для бенчмаркинга
class Benchmark {
public:
    // Измерить время работы функции F, вызванными с аргументами args
    template <typename F, typename... Args>
    static double MeasureTime(F func, Args &&...args) {
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::microseconds>(
                   end - start
        )
            .count();
    }
};

}  // namespace rsq::benchmark

#endif  // BENCHMARK_HPP
