#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class UI {
public:
    UI(SDL_Renderer* renderer);
    ~UI();
    
    // Rendering
    void RenderFPS(float fps, float frameTime);
    void RenderDebugOverlay(const std::vector<std::string>& debugInfo);
    void RenderAboutScreen();
    void RenderMainMenu();
    void RenderAPKList(const std::vector<std::string>& apkList);
    
    // Input
    bool HandleClick(int x, int y);
    
    // State
    void SetShowDebug(bool show) { m_showDebug = show; }
    void SetShowAbout(bool show) { m_showAbout = show; }
    void SetShowMenu(bool show) { m_showMenu = show; }
    
private:
    SDL_Renderer* m_renderer;
    bool m_showDebug;
    bool m_showAbout;
    bool m_showMenu;
    
    // Simple text rendering (SDL2 doesn't have built-in TTF, but we'll use basic rendering)
    void DrawText(const std::string& text, int x, int y, SDL_Color color);
    void DrawRect(int x, int y, int w, int h, SDL_Color color, bool filled = true);
    void DrawLine(int x1, int y1, int x2, int y2, SDL_Color color);
    
    // UI Colors
    SDL_Color m_textColor;
    SDL_Color m_bgColor;
    SDL_Color m_accentColor;
};
