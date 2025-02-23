#ifndef TREAP_HPP
#define TREAP_HPP

#include <irsq.hpp>

namespace rsq {

class Treap : public IRSQ {
private:
    struct Node {  // приватная структура для вершины-поддерева декартова дерева
    public:
        // поддерживаем размер поддерева, приоритет, значение в вершине, сумму в
        // поддереве, указатели на левого и правого ребенка
        std::size_t size;
        int prior;
        int value;
        int sum;
        Node *left = nullptr;
        Node *right = nullptr;

        explicit Node(int value)
            : size(1),
              value(value),
              sum(value),
              prior((rand() << 16) ^ rand()) {
        }
    };

    Node *root_ = nullptr;

    std::size_t GetNodeSize(Node *node) {
        if (!node) {
            return 0;
        }
        return node->size;
    }

    std::size_t GetNodeSum(Node *node) {
        if (!node) {
            return 0;
        }
        return node->sum;
    }

    void UpdateNode(Node *node) {
        if (!node) {
            return;
        }
        node->size = 1 + GetNodeSize(node->left) + GetNodeSize(node->right);
        node->sum =
            node->value + GetNodeSum(node->left) + GetNodeSum(node->right);
    }

    // метод для объединения левого и правого поддеревьев
    Node *Merge(Node *left, Node *right) {
        if (!left) {
            return right;
        }
        if (!right) {
            return left;
        }
        if (left->prior > right->prior) {
            left->right = Merge(left->right, right);
            UpdateNode(left);
            return left;
        } else {
            right->left = Merge(left, right->left);
            UpdateNode(right);
            return right;
        }
    }

    // метод для того, чтобы отделить от дерева поддерево из первых k вершин
    std::pair<Node *, Node *> Split(Node *node, std::size_t k) {
        if (!node) {
            return {nullptr, nullptr};
        }
        if (GetNodeSize(node->left) + 1 <= k) {
            auto [left_child, right_child] =
                Split(node->right, k - GetNodeSize(node->left) - 1);
            node->right = left_child;
            UpdateNode(node);
            return {node, right_child};
        } else {
            auto [left_child, right_child] = Split(node->left, k);
            node->left = right_child;
            UpdateNode(node);
            return {left_child, node};
        }
    }

    // вставить после первых i вершин новую вершину со значением value
    void InsertValue(std::size_t index, int value) {
        auto [left, right] = Split(root_, index);
        Node *new_node = new Node(value);
        root_ = Merge(left, Merge(new_node, right));
    }

    // удалить i-ю вершину
    void RemoveNode(std::size_t index) {
        auto [left, right_with_node] = Split(root_, index);
        auto [node, right] = Split(right_with_node, 1);
        root_ = Merge(left, right);
    }

public:
    explicit Treap(const std::vector<int> &input) : IRSQ(input) {
        for (std::size_t i = 0; i < input.size(); ++i) {
            InsertValue(i, input[i]);
        }
    }

    // для "изменения" нужно сначала удалить вершину, а потом вставить вершину с
    // новым значением
    void Update(std::size_t index, int new_value) final {
        CheckIndex(index);
        RemoveNode(index);
        InsertValue(index, new_value);
    }

    // сначала отделяем префикс размера left, он нам не нужен, затем от суффикса
    // выделим префикс размера r - l + 1
    int Query(std::size_t left, std::size_t right) final {
        CheckRange(left, right);
        auto [unnecessary_prefix, suffix] = Split(root_, left);
        auto [segment, unnecessary_suffix] = Split(suffix, right - left + 1);
        int sum = GetNodeSum(segment);
        root_ = Merge(unnecessary_prefix, Merge(segment, unnecessary_suffix));
        return sum;
    }
};

}  // namespace rsq

#endif  // TREAP_HPP
