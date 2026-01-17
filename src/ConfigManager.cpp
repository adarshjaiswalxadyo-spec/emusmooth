#include "ConfigManager.h"
#include <fstream>
#include <iostream>

ConfigManager::ConfigManager() {
    m_configPath = "config.json";
    CreateDefaultConfig();
}

ConfigManager::~ConfigManager() {
}

bool ConfigManager::LoadConfig(const std::string& filepath) {
    m_configPath = filepath;
    
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Config file not found, using defaults: " << filepath << std::endl;
        CreateDefaultConfig();
        return SaveConfig(filepath);
    }
    
    try {
        file >> m_config;
        file.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading config: " << e.what() << std::endl;
        CreateDefaultConfig();
        return false;
    }
}

bool ConfigManager::SaveConfig(const std::string& filepath) {
    std::string savePath = filepath.empty() ? m_configPath : filepath;
    
    std::ofstream file(savePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not save config to " << savePath << std::endl;
        return false;
    }
    
    try {
        file << m_config.dump(4); // Pretty print with 4 spaces
        file.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving config: " << e.what() << std::endl;
        return false;
    }
}

std::string ConfigManager::GetString(const std::string& key, const std::string& defaultValue) const {
    if (m_config.contains(key) && m_config[key].is_string()) {
        return m_config[key].get<std::string>();
    }
    return defaultValue;
}

int ConfigManager::GetInt(const std::string& key, int defaultValue) const {
    if (m_config.contains(key) && m_config[key].is_number_integer()) {
        return m_config[key].get<int>();
    }
    return defaultValue;
}

float ConfigManager::GetFloat(const std::string& key, float defaultValue) const {
    if (m_config.contains(key) && m_config[key].is_number_float()) {
        return m_config[key].get<float>();
    }
    return defaultValue;
}

bool ConfigManager::GetBool(const std::string& key, bool defaultValue) const {
    if (m_config.contains(key) && m_config[key].is_boolean()) {
        return m_config[key].get<bool>();
    }
    return defaultValue;
}

void ConfigManager::SetString(const std::string& key, const std::string& value) {
    m_config[key] = value;
}

void ConfigManager::SetInt(const std::string& key, int value) {
    m_config[key] = value;
}

void ConfigManager::SetFloat(const std::string& key, float value) {
    m_config[key] = value;
}

void ConfigManager::SetBool(const std::string& key, bool value) {
    m_config[key] = value;
}

void ConfigManager::CreateDefaultConfig() {
    m_config = json::object();
    m_config["window_width"] = 1280;
    m_config["window_height"] = 720;
    m_config["fullscreen"] = false;
    m_config["vsync"] = true;
    m_config["target_fps"] = 60;
}
