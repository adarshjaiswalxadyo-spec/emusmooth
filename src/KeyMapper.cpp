#include "KeyMapper.h"
#include <sstream>

KeyMapper::KeyMapper() {
    SetDefaultMappings();
}

KeyMapper::~KeyMapper() {
}

void KeyMapper::MapKey(SDL_Scancode scancode, const std::string& action) {
    m_keyMappings[scancode] = action;
}

std::string KeyMapper::GetAction(SDL_Scancode scancode) const {
    auto it = m_keyMappings.find(scancode);
    if (it != m_keyMappings.end()) {
        return it->second;
    }
    return "";
}

bool KeyMapper::IsKeyMapped(SDL_Scancode scancode) const {
    return m_keyMappings.find(scancode) != m_keyMappings.end();
}

std::string KeyMapper::GetKeyName(SDL_Scancode scancode) {
    const char* name = SDL_GetScancodeName(scancode);
    return name ? std::string(name) : "Unknown";
}

void KeyMapper::LoadMappings(const std::map<std::string, std::string>& mappings) {
    m_keyMappings.clear();
    for (const auto& pair : mappings) {
        // Convert string key name to SDL_Scancode
        SDL_Scancode scancode = SDL_GetScancodeFromName(pair.first.c_str());
        if (scancode != SDL_SCANCODE_UNKNOWN) {
            m_keyMappings[scancode] = pair.second;
        }
    }
}

std::map<std::string, std::string> KeyMapper::GetMappings() const {
    std::map<std::string, std::string> result;
    for (const auto& pair : m_keyMappings) {
        result[GetKeyName(pair.first)] = pair.second;
    }
    return result;
}

void KeyMapper::SetDefaultMappings() {
    m_keyMappings.clear();
    
    // Default key mappings
    m_keyMappings[SDL_SCANCODE_ESCAPE] = "quit";
    m_keyMappings[SDL_SCANCODE_F1] = "toggle_debug";
    m_keyMappings[SDL_SCANCODE_F2] = "toggle_about";
    m_keyMappings[SDL_SCANCODE_F3] = "toggle_menu";
    m_keyMappings[SDL_SCANCODE_F11] = "toggle_fullscreen";
}
