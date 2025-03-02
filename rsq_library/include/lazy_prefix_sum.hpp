#ifndef LAZY_PREFIX_SUM_HPP
#define LAZY_PREFIX_SUM_HPP

#include <prefix_sum.hpp>

namespace rsq {

class LazyPrefixSum : public IRSQ { 
private:   
    PrefixSum prefix_sum_;
    bool need_recount_;

public:
    explicit LazyPrefixSum(const std::vector<int> &input)
        : IRSQ(input),
          prefix_sum_(input),
          need_recount_(false) 
    {}

    void Update(std::size_t index, int new_value) final {
        CheckIndex(index);
        prefix_sum_.data_[index] = new_value;
        need_recount_ = true;
    }

    int Query(std::size_t left, std::size_t right) final {
        if (need_recount_) {
            prefix_sum_.RecalcPrefixSum();
            need_recount_ = false;
        }

        return prefix_sum_.Query(left, right);
    }    
};

}

#endif
