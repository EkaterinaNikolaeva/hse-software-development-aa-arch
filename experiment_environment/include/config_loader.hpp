#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <vector>

class ConfigLoader {
public:
    static std::vector<int> loadConfig(const std::string &filename) {
        auto path = PROJECT_ROOT + filename;
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
