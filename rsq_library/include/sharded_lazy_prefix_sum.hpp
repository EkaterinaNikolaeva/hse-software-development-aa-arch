#ifndef SHARDED_LAZY_PREFIX_SUM_HPP
#define SHARDED_LAZY_PREFIX_SUM_HPP

#include <sharded_prefix_sum.hpp>
#include <set>

namespace rsq {

class ShardedLazyPrefixSum : public IRSQ { 
private:   
    struct UpdateQuery {
        std::size_t index;
        int new_value;
    };

    ShardedPrefixSum prefix_sum_;
    std::vector<UpdateQuery> pending_updates_;

public:
    explicit ShardedLazyPrefixSum(const std::vector<int> &input)
        : IRSQ(input),
          prefix_sum_(input),
          pending_updates_() 
    {}

    void Update(std::size_t index, int new_value) final {
        CheckIndex(index);
        pending_updates_.emplace_back(index, new_value);
    }

    int Query(std::size_t left, std::size_t right) final {
        for (auto [idx, value] : pending_updates_) {
            prefix_sum_.Update(idx, value);
        }
        pending_updates_.clear();


        return Query(left, right);
    }    
};

}

#endif