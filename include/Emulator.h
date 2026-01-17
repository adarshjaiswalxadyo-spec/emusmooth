#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>
#include <chrono>
#include "ConfigManager.h"
#include "KeyMapper.h"
#include "APKManager.h"
#include "UI.h"

class Emulator {
public:
    Emulator();
    ~Emulator();
    
    bool Initialize();
    void Run();
    void Shutdown();
    
    bool IsRunning() const { return m_running; }
    
private:
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    void UpdateFPS(float deltaTime);
    
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_running;
    
    // FPS tracking
    float m_fps;
    float m_frameTime;
    std::chrono::high_resolution_clock::time_point m_lastFrameTime;
    std::chrono::high_resolution_clock::time_point m_fpsUpdateTime;
    int m_frameCount;
    
    // Frame pacing
    const float m_targetFPS = 60.0f;
    const float m_targetFrameTime = 1.0f / m_targetFPS;
    
    // Components
    std::unique_ptr<ConfigManager> m_configManager;
    std::unique_ptr<KeyMapper> m_keyMapper;
    std::unique_ptr<APKManager> m_apkManager;
    std::unique_ptr<UI> m_ui;
    
    // State
    bool m_showDebugOverlay;
    bool m_showAboutScreen;
    bool m_showMainMenu;
};
