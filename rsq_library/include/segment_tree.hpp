#ifndef SEGMENT_TREE_HPP
#define SEGMENT_TREE_HPP

#include <irsq.hpp>
#include <vector>

namespace rsq {

class SegmentTree : public IRSQ {
private:
    std::vector<int> sum_tree_;

    void UpdateNodeValue(std::size_t node) {
        sum_tree_[node] = sum_tree_[node * 2 + 1] + sum_tree_[node * 2 + 2];
    }

    void BuildTree(
        const std::vector<int> &input,
        std::size_t node,
        std::size_t left,
        std::size_t right
    ) {
        if (left + 1 == right) {
            sum_tree_[node] = input[left];
            return;
        }
        std::size_t middle = (left + right) / 2;
        BuildTree(input, node * 2 + 1, left, middle);
        BuildTree(input, node * 2 + 2, middle, right);
        UpdateNodeValue(node);
    }

    void UpdateInternal(
        std::size_t node,
        std::size_t left,
        std::size_t right,
        std::size_t index,
        int new_value
    ) {
        if (left + 1 == right) {
            sum_tree_[node] = new_value;
            return;
        }
        std::size_t middle = (left + right) / 2;
        if (index < middle) {
            UpdateInternal(node * 2 + 1, left, middle, index, new_value);
        } else {
            UpdateInternal(node * 2 + 2, middle, right, index, new_value);
        }
        UpdateNodeValue(node);
    }

    int QueryInternal(
        std::size_t node,
        std::size_t left,
        std::size_t right,
        std::size_t query_left,
        std::size_t query_right
    ) {
        if (query_left <= left && right <= query_right) {
            return sum_tree_[node];
        }
        if (left >= query_right || right <= query_left) {
            return 0;
        }
        std::size_t middle = (left + right) / 2;
        int left_node_sum =
            QueryInternal(node * 2 + 1, left, middle, query_left, query_right);
        int right_node_sum =
            QueryInternal(node * 2 + 2, middle, right, query_left, query_right);
        return left_node_sum + right_node_sum;
    }

public:
    explicit SegmentTree(const std::vector<int> &input) : IRSQ(input) {
        sum_tree_.resize(INPUT_ARRAY_LENGTH_ * 4);
        if (INPUT_ARRAY_LENGTH_ > 0) {
            BuildTree(input, 0, 0, INPUT_ARRAY_LENGTH_);
        }
    }

    void Update(std::size_t index, int new_value) final {
        CheckIndex(index);
        UpdateInternal(0, 0, INPUT_ARRAY_LENGTH_, index, new_value);
    }

    int Query(std::size_t left, std::size_t right) final {
        CheckRange(left, right);
        return QueryInternal(0, 0, INPUT_ARRAY_LENGTH_, left, right + 1);
    }
};

}  // namespace rsq

#endif  // SEGMENT_TREE_HPP
