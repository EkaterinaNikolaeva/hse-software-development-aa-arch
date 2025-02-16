#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <vector>

// Загружает конфиг из JSON-файла и извлекает список размеров для тестов.
//
// Параметры:
// - **filename**: имя конфигурационного файла (относительный путь).
//
// Функция:
// - Формирует полный путь к файлу, используя `PROJECT_ROOT`.
// - Открывает файл и считывает его содержимое в объект `nlohmann::json`.
// - Проверяет наличие и корректность массива `"random_sizes"`.
// - Возвращает этот массив как `std::vector<int>`.
//
// Если файл не удаётся открыть или формат некорректен, выбрасывается
// `std::runtime_error`.

class ConfigLoader {
public:
    static std::vector<int> loadConfig(const std::string &filename) {
        auto path = PROJECT_ROOT + '/' + filename;
        std::ifstream file(path);
        if (!file) {
            throw std::runtime_error(
                "Error: Failed to open config file: " + path
            );
        }

        nlohmann::json config;
        file >> config;

        if (!config.contains("random_sizes") ||
            !config["random_sizes"].is_array()) {
            throw std::runtime_error(
                "Error: Invalid config format. 'random_sizes' array is missing "
                "or "
                "incorrect."
            );
        }

        return config["random_sizes"].get<std::vector<int>>();
    }
};

#endif  // CONFIG_LOADER_HPP
