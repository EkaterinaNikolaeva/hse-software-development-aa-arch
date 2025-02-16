#ifndef RSQ_CONSISTENCY_CHECKER_HPP
#define RSQ_CONSISTENCY_CHECKER_HPP

#include <irsq.hpp>
#include <naive.hpp>
#include <vector>

namespace rsq::utils {

template <typename T>
class RSQConsistencyChecker {
private:
    std::size_t data_size_;
    NaiveRSQ naive_rsq_;
    T custom_rsq_;

public:
    explicit RSQConsistencyChecker(const std::vector<int> &input)
        : naive_rsq_(input), custom_rsq_(input) {
    }

    int CheckQuery(std::size_t left, std::size_t right) {
        int naive_sum = naive_rsq_.Query(left, right);
        int custom_sum = custom_rsq_.Query(left, right);
        EXPECT_EQ(naive_sum, custom_sum);
        return naive_sum;
    }

    void Update(std::size_t index, int value) {
        naive_rsq_.Update(index, value);
        custom_rsq_.Update(index, value);
    }

    void SimpleCheckUpdate(std::size_t index, int value) {
        naive_rsq_.Update(index, value);
        custom_rsq_.Update(index, value);
        CheckQuery(index, index);
    }

    void FullCheck() {
        for (std::size_t l = 0; l < data_size_; ++l) {
            for (std::size_t r = l; r < data_size_; ++r) {
                CheckQuery(l, r);
            }
        }
    }
};

}  // namespace rsq::utils

#endif  // RSQ_CONSISTENCY_CHECKER_HPP