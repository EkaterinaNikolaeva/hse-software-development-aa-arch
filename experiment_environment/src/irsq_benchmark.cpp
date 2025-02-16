#include <benchmark/benchmark.h>
#include <experiment_manager_google.hpp>
#include <experiment_manager_naive.hpp>
#include <functional>
#include <memory>
#include <naive.hpp>
#include <segment_tree.hpp>
#include <vector>
#include "config_loader.hpp"
#include "random_data_generator.hpp"

// Конфиг должен содержать список размеров тестируемых наборов данных.
// Пример:
//
// ```
// {
//   "random_sizes": [10, 100, 10000]
// }
//```
//
// Здесь "random_sizes" — это массив, в котором указываются размеры входных
// данных, использующиеся для тестирования различных алгоритмов рандомными
// тестами.
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

        rsq::benchmark::ExperimentManagerGoogle experimentManagerGoogle(
            test_sizes
        );
        experimentManagerGoogle.RunExperiments();
        rsq::benchmark::ExperimentManagerNaive experimentManagerNaive(test_sizes
        );
        experimentManagerNaive.RunExperiments();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
