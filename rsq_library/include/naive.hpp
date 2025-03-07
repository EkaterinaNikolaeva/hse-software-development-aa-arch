#ifndef NAIVE_HPP
#define NAIVE_HPP

#include <irsq.hpp>
#include <vector>

namespace rsq {

// Класс наивного решения задачи RSQ
class NaiveRSQ : public IRSQ {
private:
    std::vector<int> data_;

public:
    explicit NaiveRSQ(const std::vector<int> &input)
        : IRSQ(input), data_(input) {
    }

    // Асимптотика - O(1)
    void Update(std::size_t index, int value) override {
        CheckIndex(index);
        data_[index] = value;
    }

    // Асимптотика - O(r - l + 1)
    int Query(std::size_t left, std::size_t right) override {
        CheckRange(left, right);
        int sum = 0;
        for (std::size_t i = left; i <= right; ++i) {
            sum += data_[i];
        }
        return sum;
    }
};

}  // namespace rsq

#endif  // NAIVE_HPP
