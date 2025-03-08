#include <experiment_manager_naive.hpp>
#include <functional>
#include <memory>
#include <naive.hpp>
#include <vector>
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
        std::vector<int> test_sizes{10, 
                                    100, 
                                    1000, 
                                    10000, 
                                    100000, 
                                    1000000,
                                    10000000};

        // rsq::benchmark::ExperimentManagerGoogle experimentManagerGoogle(
        //     test_sizes
        // );
        // experimentManagerGoogle.RunExperiments();

        rsq::benchmark::ExperimentManagerNaive experimentManagerNaive(test_sizes
        );
        experimentManagerNaive.RunExperiments();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
