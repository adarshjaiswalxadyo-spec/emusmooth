#include "Emulator.h"
#include <iostream>
#include <algorithm>
#include <chrono>

Emulator::Emulator()
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_running(false)
    , m_fps(0.0f)
    , m_frameTime(0.0f)
    , m_frameCount(0)
    , m_showDebugOverlay(false)
    , m_showAboutScreen(false)
    , m_showMainMenu(true)
{
    m_lastFrameTime = std::chrono::high_resolution_clock::now();
    m_fpsUpdateTime = m_lastFrameTime;
}

Emulator::~Emulator() {
    Shutdown();
}

bool Emulator::Initialize() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Initialize config manager
    m_configManager = std::make_unique<ConfigManager>();
    m_configManager->LoadConfig();
    
    // Get window settings from config
    int width = m_configManager->GetWindowWidth();
    int height = m_configManager->GetWindowHeight();
    bool fullscreen = m_configManager->GetFullscreen();
    
    // Create window
    Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    if (fullscreen) {
        windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    
    m_window = SDL_CreateWindow(
        "Emulator - Built by Adarsh Jaiswal",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        windowFlags
    );
    
    if (!m_window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Create renderer (GPU accelerated)
    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (!m_renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Initialize components
    m_keyMapper = std::make_unique<KeyMapper>();
    m_keyMapper->SetDefaultMappings();
    
    m_apkManager = std::make_unique<APKManager>();
    m_apkManager->SetInstallDirectory("apks");
    
    m_ui = std::make_unique<UI>(m_renderer);
    
    m_running = true;
    
    std::cout << "Emulator initialized successfully!" << std::endl;
    return true;
}

void Emulator::Run() {
    while (m_running) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto deltaTime = std::chrono::duration<float>(currentTime - m_lastFrameTime).count();
        m_lastFrameTime = currentTime;
        
        // Frame pacing - limit to target FPS
        if (deltaTime < m_targetFrameTime) {
            float sleepTime = (m_targetFrameTime - deltaTime) * 1000.0f;
            SDL_Delay(static_cast<Uint32>(sleepTime));
            deltaTime = m_targetFrameTime;
        }
        
        m_frameTime = deltaTime;
        UpdateFPS(deltaTime);
        
        ProcessEvents();
        Update(deltaTime);
        Render();
    }
}

void Emulator::ProcessEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_running = false;
                break;
                
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    if (m_showAboutScreen) {
                        m_showAboutScreen = false;
                    } else if (m_showMainMenu) {
                        m_showMainMenu = false;
                    } else {
                        m_running = false;
                    }
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_F1) {
                    m_showDebugOverlay = !m_showDebugOverlay;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_F2) {
                    m_showAboutScreen = !m_showAboutScreen;
                }
                else if (event.key.keysym.scancode == SDL_SCANCODE_F3) {
                    m_showMainMenu = !m_showMainMenu;
                }
                break;
                
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    // Window was resized
                }
                break;
        }
    }
}

void Emulator::Update(float deltaTime) {
    // Update logic here
    // This is where you would update emulator state, APK execution, etc.
}

void Emulator::Render() {
    // Clear screen
    SDL_SetRenderDrawColor(m_renderer, 20, 20, 30, 255);
    SDL_RenderClear(m_renderer);
    
    // Render main content
    if (m_showMainMenu) {
        m_ui->RenderMainMenu();
    }
    
    // Render APK content area (placeholder)
    SDL_SetRenderDrawColor(m_renderer, 30, 30, 40, 255);
    SDL_Rect contentRect = {100, 100, 1080, 520};
    SDL_RenderFillRect(m_renderer, &contentRect);
    
    // Render UI overlays
    if (m_showDebugOverlay) {
        std::vector<std::string> debugInfo = {
            "FPS: " + std::to_string(static_cast<int>(m_fps)),
            "Frame Time: " + std::to_string(m_frameTime * 1000.0f) + " ms",
            "Window: " + std::to_string(m_configManager->GetWindowWidth()) + "x" + 
                       std::to_string(m_configManager->GetWindowHeight()),
            "Press F1 to toggle debug overlay",
            "Press F2 to show about screen",
            "Press F3 to toggle main menu"
        };
        m_ui->RenderDebugOverlay(debugInfo);
    }
    
    if (m_showAboutScreen) {
        m_ui->RenderAboutScreen();
    }
    
    // Always render FPS counter
    m_ui->RenderFPS(m_fps, m_frameTime);
    
    // Present
    SDL_RenderPresent(m_renderer);
}

void Emulator::UpdateFPS(float deltaTime) {
    m_frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<float>(currentTime - m_fpsUpdateTime).count();
    
    if (elapsed >= 1.0f) {
        m_fps = m_frameCount / elapsed;
        m_frameCount = 0;
        m_fpsUpdateTime = currentTime;
    }
}

void Emulator::Shutdown() {
    // Save config
    if (m_configManager) {
        m_configManager->SaveConfig();
    }
    
    // Cleanup SDL
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    
    SDL_Quit();
}
