# hse-software-development-aa-arch
![Build Status](https://github.com/EkaterinaNikolaeva/hse-software-development-aa-arch/actions/workflows/ci.yml/badge.svg)
[![codecov](https://codecov.io/gh/EkaterinaNikolaeva/hse-software-development-aa-arch/graph/badge.svg?token=3TD7AGNN9H)](https://codecov.io/gh/EkaterinaNikolaeva/hse-software-development-aa-arch)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/c6738c14413447e78cebd7ce79f8e130)](https://app.codacy.com/gh/EkaterinaNikolaeva/hse-software-development-aa-arch/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
![License](https://img.shields.io/github/license/EkaterinaNikolaeva/hse-software-development-aa-arch)

## Описание репозитория

Данный репозиторий содержит библиотеку и экспериментальную среду для решения задачи вычисления суммы на отрезке массива с возможностью обновления отдельных элементов. Язык реализации - C++.

## Постановка задачи RSQ

Дан массив целых чисел. Необходимо отвечать на запросы двух видов:

1. Посчитать сумму на отрезке [l, r] массива

2. Присвоить $i$-ому элементу массива значение $k$

## Установка

1. Склонируйте репозиторий

```
git clone https://github.com/EkaterinaNikolaeva/hse-software-development-aa-arch.git
```

2. Установите зависимости

```
sudo apt-get install -y cmake g++ lcov libgtest-dev libbenchmark-dev
```

## Использование

1. Библиотека является header-only, поэтому для использования достаточно просто импортировать необходимые файлы
2. Для запусков тестов

* Найстройте CMake:
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage" -DCMAKE_EXE_LINKER_FLAGS="--coverage"
```
* Соберите
```
cmake --build build
```

* Чтобы запустить тесты производительности, выполните:
```
./build/my_benchmark
```
* Чтобы запустить юнит-тесты
```
ctest --test-dir build/rsq_library/tests/
```
* Чтобы посчитать покрытие кода

```
lcov --capture --directory build --output-file coverage.info && lcov --remove coverage.info '/usr/*' --output-file coverage.info && lcov --list coverage.info
```
