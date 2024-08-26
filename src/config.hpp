#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <stdint.h>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <unordered_set>

#include <boost/json.hpp>

namespace json = boost::json;

namespace config
{
    // Path to the json config
    inline const std::string config_path{"../config.json"};

    inline std::string bot_token;
    inline std::unordered_set<int64_t> allowed_user_ids;
    inline std::string sudo_password;

    inline void init()
    {
        std::ifstream config_file{config_path};

        if (!config_file.is_open())
        {
            throw std::invalid_argument{
                "Config file was not found at the specified path: " + 
                std::filesystem::canonical(config::config_path).string()};
        }
        
        std::string config_data;
        size_t config_file_size = std::filesystem::file_size(config_path);
        config_data.resize(config_file_size);

        config_file.read(config_data.data(), config_file_size);
        json::object config_json = json::parse(config_data).as_object();
        
        // Initialize config variables with values from json
        bot_token = config_json.at("bot_token").as_string();
        for (const auto& allowed_user_id : config_json.at("allowed_user_ids").as_array())
        {
            allowed_user_ids.emplace(allowed_user_id.to_number<int64_t>());
        }

        sudo_password = config_json.at("sudo_password").as_string();
    }
}

#endif