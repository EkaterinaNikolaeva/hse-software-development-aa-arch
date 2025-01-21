# Структура проекта и основные компоненты

## 1. Структура проекта

```cpp
/RSQ_Library              # Модуль с алгоритмами RSQ (header-only)
  /include                # Заголовочные файлы с реализациями алгоритмов
  /tests                  # Unit-тесты для проверки алгоритмов

/Experiment_Environment   # Модуль экспериментальной среды
  /include                # Заголовочные файлы для экспериментальной среды
  /src                    # Исходный код для экспериментальной среды
  /data                   # Пример входных данных для тестирования
  /results                # Результаты тестов и сравнений

/docs                     # Документация
```

## 2.Основные компоненты проекта

### 1. Алгоритмы RSQ (header-only библиотека)

Реализует 8 структур данных для RSQ. Каждый алгоритм представлен отдельным классом, реализующим базовый интерфейс для унификации работы. Также в этом модуле находятся юнит-тесты для проверки правильности работы алгоритмов.

* Базовый интерфейс

```cpp
class IRSQ {
  virtual int Query(int left, int right) = 0;
  virtual void Update(int index, int value) = 0;
  virtual ~IRSQ() = default;
};
```

* Юнит-тесты

```cpp
class ITestRSQ {
public:
  void TestQuery() {
    // тестирование метода Query
  }
  void TestUpdate() {
    // тестирование метода Update
  }
};
```

### 2. Экспериментальная среда

#### 1. Конфигурация экспериментов

Конфигурация задаётся прямо в коде для упрощения, без внешних файлов. Пример:

```cpp
struct Config {
    std::vector<RSQAlgorithm> algorithms = {RSQAlgorithm::PrefixSum, RSQAlgorithm::SegmentTree, RSQAlgorithm::FenwickTree};
    std::vector<int> dataSizes = {100, 1000, 10000};
    int queryCount = 100;
};
```

#### 2. Менеджер экспериментов

Основной компонент, который управляет всеми этапами эксперимента. Он будет:

* Генерировать данные в зависимости от конфигурации.
* Проводить измерение времени работы и количества памяти через Benchmark.
* Выводить результаты на экран и в файл.

Примерная структура класса, детали могут меняться

```cpp
class ExperimentManager {
public:
    // Установка конфигурации для экспериментов
    void setConfig(const Config& config);

    // Добавление алгоритма для тестирования
    void addAlgorithm(RSQAlgorithm algorithm);

    // Генерация данных (случайные, монотонные и т.д.)
    void generateData(size_t dataSize, const std::string& dataType);

    // Добавление пользовательских данных для тестирования
    void setCustomData(const std::vector<int>& data); 
    void setCustomDataFromFile(const std::string& filePath); 

    // Запуск экспериментов
    void runExperiments();

    // Получение результатов
    std::vector<std::string> getResults() const;

    // Визуализация результатов
    void visualizeResults(const std::string& outputPath, const std::string& graphType = "bar");
};
```

#### 4. Модуль визуализации

Визуализация реализуется в отдельном классе, который включён в менеджер. Примерная структура класса, детали могут меняться

```cpp
class Visualizer {
public:
    // Построение гистограммы
    void createBarChart(const std::unordered_map<RSQAlgorithm, double>& performanceMetrics, 
                        const std::string& outputPath);

    // Построение линейного графика
    void createLineChart(const std::unordered_map<RSQAlgorithm, std::vector<double>>& performanceMetricsBySize, 
                         const std::string& outputPath);
};
```
