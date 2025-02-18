#ifndef SQRT_RSQ_HPP
#define SQRT_RSQ_HPP

#include <cmath>
#include <irsq.hpp>
#include <vector>

namespace rsq {

class SqrtRSQ : public IRSQ {
private:
    const std::size_t BLOCK_SIZE_;  // Размер блока, на которые будем делить
                                    // массив и предподсчитывать сумму
    std::vector<int> block_sum_;  // Суммы в соответсвующих блоках
    std::vector<int> data_;  // Поддерживается актуальное состояние массива

    void BuildSqrtBlocks() {
        block_sum_.resize(
            (INPUT_ARRAY_LENGTH_ + BLOCK_SIZE_ - 1) / BLOCK_SIZE_
        );
        for (std::size_t i = 0; i < INPUT_ARRAY_LENGTH_; ++i) {
            block_sum_[i / BLOCK_SIZE_] += data_[i];
        }
    }

    int GetSumCompleteBlocks(std::size_t left_block, std::size_t right_block) {
        int sum = 0;
        for (std::size_t block = left_block + 1; block < right_block; ++block) {
            sum += block_sum_[block];
        }
        return sum;
    }

    // Посчитать сумму на блоке, частично входящем в запрос, слева
    int GetSumLeftBlockPart(std::size_t left, std::size_t left_block) {
        int sum = 0;
        for (std::size_t i = left; i < BLOCK_SIZE_ * (left_block + 1); ++i) {
            sum += data_[i];
        }
        return sum;
    }

    // Посчитать сумму на блоке, частично входящем в запрос, справа
    int GetSumRightBlockPart(std::size_t right, std::size_t right_block) {
        int sum = 0;
        for (std::size_t i = BLOCK_SIZE_ * right_block; i <= right; ++i) {
            sum += data_[i];
        }
        return sum;
    }

    // Посчитать сумму методом прохода по массиву. Используется для запросов,
    // лежащих внутри одного блока
    int GetSumNaive(std::size_t left, std::size_t right) {
        int sum = 0;
        for (std::size_t i = left; i <= right; ++i) {
            sum += data_[i];
        }
        return sum;
    }

public:
    explicit SqrtRSQ(const std::vector<int> &input)
        : IRSQ(input),
          BLOCK_SIZE_(std::trunc(std::sqrt(input.size()))),
          data_(input) {
        BuildSqrtBlocks();
    }

    void Update(std::size_t index, int new_value) final {
        CheckIndex(index);
        block_sum_[index / BLOCK_SIZE_] -=
            data_[index];  // Вычитаем старое значение, прибавляем новое в сумме
                           // в соответсвующем блоке
        block_sum_[index / BLOCK_SIZE_] += new_value;
        data_[index] = new_value;  // Поддерживаем в data_ актуальную информацию
    }

    int Query(std::size_t left, std::size_t right) final {
        CheckRange(left, right);
        std::size_t left_block = left / BLOCK_SIZE_;
        std::size_t right_block = right / BLOCK_SIZE_;
        if (left_block ==
            right_block) {  // Если весь запрос находится в одном блоке
            return GetSumNaive(left, right);
        }
        return GetSumCompleteBlocks(left_block, right_block) +
               GetSumLeftBlockPart(left, left_block) +
               GetSumRightBlockPart(right, right_block);
    }
};

}  // namespace rsq

#endif  // SQRT_RSQ_HPP
