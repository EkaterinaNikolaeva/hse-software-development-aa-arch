#ifndef DOWN_SEGMENT_TREE_HPP
#define DOWN_SEGMENT_TREE_HPP

#include <irsq.hpp>
#include <vector>

namespace rsq {

class DownSegmentTree : public IRSQ {
private:
    std::vector<int>
        sum_tree_;  // размера 2n, в последних n вершинах - сам массив, в 1
                    // вершине - корень, дети вершины i - 2*i и 2*i+1

    void BuildTree(const std::vector<int> &input) {
        sum_tree_.resize(2 * INPUT_ARRAY_LENGTH_);
        for (std::size_t i = 0; i < INPUT_ARRAY_LENGTH_; ++i) {
            sum_tree_[i + INPUT_ARRAY_LENGTH_] = input[i];
        }
        for (int i = static_cast<int>(INPUT_ARRAY_LENGTH_) - 1; i > 0; --i) {
            sum_tree_[i] = sum_tree_[2 * i] + sum_tree_[2 * i + 1];
        }
    }

public:
    explicit DownSegmentTree(const std::vector<int> &input) : IRSQ(input) {
        BuildTree(input);
    }

    void Update(std::size_t index, int new_value) final {
        CheckIndex(index);
        sum_tree_[index += INPUT_ARRAY_LENGTH_] =
            new_value;  // прибавляем к листу
        for (index /= 2; index >= 1; index /= 2) {
            sum_tree_[index] =
                sum_tree_[2 * index] +
                sum_tree_[2 * index + 1];  // пересчитываем всех предков
        }
    }

    int Query(std::size_t left, std::size_t right) final {
        CheckRange(left, right);
        int sum = 0;
        for (left += INPUT_ARRAY_LENGTH_, right += INPUT_ARRAY_LENGTH_;
             left <= right;
             left /= 2, right /= 2) {  // вычисляем сумму от листов к корню
            if (left % 2 == 1) {
                sum += sum_tree_[left++];
            }
            if (right % 2 == 0) {
                sum += sum_tree_[right--];
            }
        }
        return sum;
    }
};

}  // namespace rsq

#endif  // DOWN_SEGMENT_TREE_HPP