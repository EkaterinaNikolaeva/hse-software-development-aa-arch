#ifndef FENWICK_HPP
#define FENWICK_HPP

#include <irsq.hpp>
#include <vector>

namespace rsq {

class FenwickTree : public IRSQ {
private:
    std::vector<int> data_;

    void UpdateInternal(std::size_t index, int value) {
        while (index < data_.size()) {
            data_[index] += value;
            index += index & -index;
        }
    }

    int QueryInternal(std::size_t index) const {
        int sum = 0;
        while (index > 0) {
            sum += data_[index];
            index -= index & -index;
        }
        return sum;
    }

public:
    explicit FenwickTree(const std::vector<int> &input) : IRSQ(input) {
        data_.resize(input.size() + 1, 0);
        for (std::size_t i = 0; i < input.size(); ++i) {
            Update(i, input[i]);
        }
    }

    int Query(std::size_t left, std::size_t right) override {
        CheckRange(left, right);
        return QueryInternal(right + 1) - QueryInternal(left);
    }

    void Update(std::size_t index, int value) override {
        CheckIndex(index);
        int diff = value - Query(index, index);
        UpdateInternal(index + 1, diff);
    }
};

}  // namespace rsq

#endif  // FENWICK_HPP
