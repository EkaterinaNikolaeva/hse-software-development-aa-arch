#ifndef PREFIX_SUM_HPP
#define PREFIX_SUM_HPP

#include <irsq.hpp>
#include <set>

namespace rsq {

class PrefixSum : public IRSQ { 
public:
    explicit PrefixSum(const std::vector<int>& input)
        : IRSQ(input),
          prefix_sum_(input.size() + 1, 0) 
    {
        for (size_t i = 0; i < input.size(); ++i) {
            prefix_sum_[i + 1] = prefix_sum_[i] + input[i];
        }
    }

    void Update(std::size_t index, int new_value) final {
        CheckIndex(index);        
        int64_t old_value = prefix_sum_[index + 1] - prefix_sum_[index];
        int64_t diff = static_cast<int64_t>(new_value) - old_value;
        
        for (size_t i = index + 1; i < prefix_sum_.size(); ++i) {
            prefix_sum_[i] += diff;
        }
    }

    int Query(std::size_t left, std::size_t right) final {
        CheckIndex(left);
        CheckIndex(right);
        return static_cast<int>(prefix_sum_[right + 1] - prefix_sum_[left]);
    }

private:   
    std::vector<int64_t> prefix_sum_;
};

}

#endif // PREFIX_SUM_HPP
