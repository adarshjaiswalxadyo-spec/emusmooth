#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <functional>

class KeyMapper {
public:
    KeyMapper();
    ~KeyMapper();
    
    // Map a key to an action
    void MapKey(SDL_Scancode scancode, const std::string& action);
    
    // Get action for a key
    std::string GetAction(SDL_Scancode scancode) const;
    
    // Check if key is mapped
    bool IsKeyMapped(SDL_Scancode scancode) const;
    
    // Get key name
    static std::string GetKeyName(SDL_Scancode scancode);
    
    // Load/Save mappings
    void LoadMappings(const std::map<std::string, std::string>& mappings);
    std::map<std::string, std::string> GetMappings() const;
    
    // Default mappings
    void SetDefaultMappings();
    
private:
    std::map<SDL_Scancode, std::string> m_keyMappings;
};
