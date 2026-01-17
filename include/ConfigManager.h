#pragma once

#include <string>
#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigManager {
public:
    ConfigManager();
    ~ConfigManager();
    
    bool LoadConfig(const std::string& filepath = "config.json");
    bool SaveConfig(const std::string& filepath = "config.json");
    
    // Getters
    std::string GetString(const std::string& key, const std::string& defaultValue = "") const;
    int GetInt(const std::string& key, int defaultValue = 0) const;
    float GetFloat(const std::string& key, float defaultValue = 0.0f) const;
    bool GetBool(const std::string& key, bool defaultValue = false) const;
    
    // Setters
    void SetString(const std::string& key, const std::string& value);
    void SetInt(const std::string& key, int value);
    void SetFloat(const std::string& key, float value);
    void SetBool(const std::string& key, bool value);
    
    // Window settings
    int GetWindowWidth() const { return GetInt("window_width", 1280); }
    int GetWindowHeight() const { return GetInt("window_height", 720); }
    bool GetFullscreen() const { return GetBool("fullscreen", false); }
    
    void SetWindowWidth(int width) { SetInt("window_width", width); }
    void SetWindowHeight(int height) { SetInt("window_height", height); }
    void SetFullscreen(bool fullscreen) { SetBool("fullscreen", fullscreen); }
    
private:
    json m_config;
    std::string m_configPath;
    
    void CreateDefaultConfig();
};
