#ifndef RSQ_RANDOM_DATA_GENERATOR_HPP
#define RSQ_RANDOM_DATA_GENERATOR_HPP

#include <random>
#include <vector>

namespace rsq::utils {

class RandomDataGenerator {
private:
    std::mt19937 rng_;
    std::uniform_int_distribution<int> min_max_dis_;
    std::uniform_real_distribution<double> zero_one_dis_;
    std::uniform_int_distribution<std::size_t> index_dis_;
    std::bernoulli_distribution action_dis_;

public:
    explicit RandomDataGenerator(
        const size_t vector_size = 100,
        const int min_element = -100,
        const int max_element = 100,
        const double action_probability = 0.5
    )
        : rng_(std::time(nullptr)),
          min_max_dis_(min_element, max_element),
          zero_one_dis_(0.0, 1.0),
          index_dis_(0, vector_size - 1),
          action_dis_(action_probability) {
        if (vector_size == 0) {
            throw std::invalid_argument("Vector size must be greater than zero."
            );
        }
        if (min_element > max_element) {
            throw std::invalid_argument(
                "Minimum element cannot be greater than maximum element."
            );
        }
        if (action_probability < 0.0 || action_probability > 1.0) {
            throw std::invalid_argument(
                "Action probability must be between zero and one."
            );
        }
    }

    int GetRandomInt() {
        return min_max_dis_(rng_);
    }

    std::size_t GetRandomIndex() {
        return index_dis_(rng_);
    }

    bool CheckChangeAction() {
        return action_dis_(rng_);
    }

    std::vector<int> GenerateRandomVector() {
        std ::vector<int> result(index_dis_.max() + 1);
        for (auto &value : result) {
            value = GetRandomInt();
        }
        return result;
    }
};

}  // namespace rsq::utils

#endif
