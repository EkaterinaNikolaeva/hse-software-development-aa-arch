#ifndef SHARDED_PREFIX_SUM_HPP
#define SHARDED_PREFIX_SUM_HPP

#include <irsq.hpp>
#include <vector>

namespace rsq {

class ShardedPrefixSum : public IRSQ {
private:
    static const std::size_t SHARD_SIZE = 5;

    struct Shard {
        std::vector<int> prefix_sum;
        int sum;
    };

    std::vector<int> data_;
    std::vector<Shard> shards_;

    std::size_t ToShardIndex(std::size_t value_index) {
        return value_index / SHARD_SIZE;
    }

    std::size_t ToInShardIndex(std::size_t value_index) {
        return value_index % SHARD_SIZE + 1;
    }

public: 
    explicit ShardedPrefixSum(const std::vector<int> &input)
        : IRSQ(input),
          data_(input) {
        for (std::size_t i = 0; i < data_.size(); i++) {
            std::size_t shard_index = ToShardIndex(i);
            if (shards_.size() < shard_index) {
                shards_.emplace_back(std::vector<int>(1, 0), 0);
            }
            shards_.back().prefix_sum.push_back(data_[i] + shards_.back().prefix_sum.back());
            shards_.back().sum += data_[i];
        }
    }

    void Update(std::size_t index, int new_value) final {
        CheckIndex(index);
        
        int old_value = data_[index];
        std::size_t shard_index = ToShardIndex(index);
        std::size_t inshard_index = ToInShardIndex(index);
        
        int delta = new_value - old_value;
        for (std::size_t i = inshard_index; i < shards_[shard_index].prefix_sum.size(); i++) {
            shards_[shard_index].prefix_sum[i] += delta;
        }
        shards_[shard_index].sum += delta;
    }

    int Query(std::size_t left, std::size_t right) final {
        CheckRange(left, right);
        
        std::size_t left_shard = ToShardIndex(left);
        std::size_t left_inshard = ToInShardIndex(left);
        std::size_t right_shard = ToShardIndex(right);
        std::size_t right_inshard = ToInShardIndex(right);

        int result = 0;
        for (std::size_t i = left_shard + 1; i < right_shard; i++) {
            result += shards_[i].sum;
        }
        if (left_shard == right_shard) {
            result += shards_[right_shard].prefix_sum[right_inshard] - shards_[right_shard].prefix_sum[left_inshard - 1];
        } else {
            result += shards_[left_shard].sum - shards_[left_shard].prefix_sum[left_inshard - 1];
            result += shards_[right_shard].prefix_sum[right_inshard];
        }

        return result;
    }
};

}

#endif