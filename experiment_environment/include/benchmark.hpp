#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <chrono>
#include <functional>
#include <iostream>

#if _WIN32 || WIN64
#include <windows.h>
#include <psapi.h>
#elif __unix__ || __linux__
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <fstream>
#elif __APPLE__ || __MACH__
#include <mach/mach.h>
#include <sys/sysctl.h>
#endif

namespace rsq::benchmark {

class Benchmark {
private:
    // Physical memory usage
    static std::size_t GetMemoryUsage() {
#if _WIN32 || WIN64
        // Реализация для Windows
        const HANDLE hProcess = GetCurrentProcess();
        PROCESS_MEMORY_COUNTERS_EX pmc = {0};
        GetProcessMemoryInfo(
            hProcess, reinterpret_cast<PROCESS_MEMORY_COUNTERS *>(&pmc),
            sizeof(pmc)
        );
        return pmc.WorkingSetSize / 1024;

#elif __unix__ || __linux__
        // Реализация для Linux
        std::ifstream stream("/proc/self/status");
        std::string line;
        size_t result = 0;
        while (getline(stream, line)) {
            if (line.compare(0, 6, "VmRSS:") == 0) {
                std::string n = "";
                for (const auto &c : line) {
                    if ('0' <= c && c <= '9') {
                        n += c;
                    }
                }
                result = static_cast<size_t>(std::stoi(n));
                break;
            }
        }

        stream.close();

        return result;

#elif __APPLE__ || __MACH__
        // Реализация для macOS
        task_t targetTask = mach_task_self();
        task_vm_info_data_t ti;
        mach_msg_type_number_t count = TASK_VM_INFO_COUNT;

        const auto result = task_info(
            targetTask, TASK_VM_INFO, reinterpret_cast<task_info_t>(&ti), &count
        );
        if (result == KERN_SUCCESS) {
            return ti.phys_footprint;
        } else {
            return 0;
        }
#else
        throw std::runtime_error("Unsupported platform");
#endif
    }

    template <typename F, typename... Args>
    static int64_t MeasureTime(F func, Args &&...args) {
        auto start = std::chrono::high_resolution_clock::now();
        func(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::microseconds>(
                   end - start
        )
            .count();
    }

public:
    template <typename F, typename... Args>
    static std::string Measure(F func, Args &&...args) {
        std::size_t memory_before = GetMemoryUsage();
        auto time = MeasureTime(func, std::forward<Args>(args)...);
        std::size_t memory_after = GetMemoryUsage();

        std::ostringstream result;
        result << time << "," << memory_after - memory_before;
        return result.str();
    }
};

}  // namespace rsq::benchmark

#endif  // BENCHMARK_HPP
