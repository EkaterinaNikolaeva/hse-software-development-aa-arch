#ifndef EXPERIMENT_MANAGER_BASE_HPP
#define EXPERIMENT_MANAGER_BASE_HPP

#include <random_data_generator.hpp>
#include <vector>

namespace rsq::benchmark {

class ExperimentManagerBase {
protected:
    std::vector<int> random_sizes_;

    template <typename RSQType>
    static void MakeNaiveActions(std::size_t size) {
        std::vector<int> data(size, 1);
        RSQType rsq(data);
        for (size_t i = 0; i < size; ++i) {
            rsq.Update(i, i);
            rsq.Query(0, size - 1);
        }
    }

    template <typename RSQType>
    static void MakeRandomActions(std::size_t size) {
        rsq::utils::RandomDataGenerator generator(size);
        std::vector<int> data = generator.GenerateRandomVector();

        RSQType rsq(data);
        for (size_t i = 0; i < size; ++i) {
            rsq.Update(generator.GetRandomIndex(), generator.GetRandomInt());
            std::size_t left = generator.GetRandomIndex();
            std::size_t right = generator.GetRandomIndex();
            if (left > right) {
                std::swap(left, right);
            }
            rsq.Query(left, right);
        }
    }

    template <typename RSQType>
    static void MakeBenchmarkRandomParameterizedTest(
        std::size_t size,
        int min_element,
        int max_element,
        double update_probability
    ) {
        rsq::utils::RandomDataGenerator generator(
            size, min_element, max_element, update_probability
        );
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

    template <typename RSQType>
    static void MakeConstructor(std::size_t size) {
        rsq::utils::RandomDataGenerator generator(size);
        std::vector<int> data = generator.GenerateRandomVector();

        RSQType rsq(data);
    }
    
public:
    explicit ExperimentManagerBase(std::vector<int> sizes)
        : random_sizes_(std::move(sizes)) {
    }

    virtual void RunExperiments() = 0;

    virtual ~ExperimentManagerBase() = default;
};

}  // namespace rsq::benchmark

#endif  // EXPERIMENT_MANAGER_BASE_HPP