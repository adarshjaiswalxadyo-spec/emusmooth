#include "UI.h"
#include <sstream>
#include <iomanip>

UI::UI(SDL_Renderer* renderer)
    : m_renderer(renderer)
    , m_showDebug(false)
    , m_showAbout(false)
    , m_showMenu(false)
{
    m_textColor = {255, 255, 255, 255};
    m_bgColor = {30, 30, 40, 200};
    m_accentColor = {100, 150, 255, 255};
}

UI::~UI() {
}

void UI::RenderFPS(float fps, float frameTime) {
    // Render FPS in top-right corner
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << fps << " FPS";
    std::string fpsText = oss.str();
    
    // Simple text rendering using rectangles (SDL2 doesn't have built-in text rendering)
    // In a production app, you'd use SDL_ttf
    int x = 10;
    int y = 10;
    
    // Background for FPS counter
    DrawRect(x - 5, y - 5, 120, 25, {0, 0, 0, 180}, true);
    
    // Draw FPS text (simplified - using colored rectangles as placeholder)
    // For real text, you'd need SDL_ttf or similar
    SDL_Color color = (fps >= 55.0f) ? SDL_Color{0, 255, 0, 255} : 
                      (fps >= 30.0f) ? SDL_Color{255, 255, 0, 255} : 
                      SDL_Color{255, 0, 0, 255};
    
    // Placeholder: draw a small indicator
    DrawRect(x, y, 100, 15, color, true);
}

void UI::RenderDebugOverlay(const std::vector<std::string>& debugInfo) {
    int x = 10;
    int y = 50;
    int lineHeight = 20;
    int padding = 10;
    
    // Calculate overlay size
    int maxWidth = 300;
    int height = static_cast<int>(debugInfo.size()) * lineHeight + padding * 2;
    
    // Background
    DrawRect(x, y, maxWidth, height, m_bgColor, true);
    
    // Border
    SDL_Rect border = {x, y, maxWidth, height};
    SDL_SetRenderDrawColor(m_renderer, m_accentColor.r, m_accentColor.g, m_accentColor.b, 255);
    SDL_RenderDrawRect(m_renderer, &border);
    
    // Draw debug info (simplified - would need text rendering in production)
    int currentY = y + padding;
    for (size_t i = 0; i < debugInfo.size(); ++i) {
        // Placeholder: draw indicator for each line
        DrawRect(x + padding, currentY, 5, lineHeight - 5, m_accentColor, true);
        currentY += lineHeight;
    }
}

void UI::RenderAboutScreen() {
    int width = 600;
    int height = 400;
    int x = (1280 - width) / 2; // Center horizontally (assuming 1280 width)
    int y = (720 - height) / 2;  // Center vertically (assuming 720 height)
    
    // Background
    DrawRect(x, y, width, height, m_bgColor, true);
    
    // Border
    SDL_Rect border = {x, y, width, height};
    SDL_SetRenderDrawColor(m_renderer, m_accentColor.r, m_accentColor.g, m_accentColor.b, 255);
    SDL_RenderDrawRect(m_renderer, &border);
    
    // Title
    int titleY = y + 40;
    DrawRect(x + 20, titleY, width - 40, 3, m_accentColor, true);
    
    // About text (simplified - would need text rendering)
    int textY = titleY + 60;
    int lineHeight = 30;
    
    // Developer info
    std::vector<std::string> aboutLines = {
        "Built by Adarsh Jaiswal",
        "Web Developer",
        "Instagram: @adar.xhevil",
        "",
        "Emulator v1.0.0",
        "",
        "Press ESC to close"
    };
    
    for (size_t i = 0; i < aboutLines.size(); ++i) {
        // Placeholder: draw indicator for each line
        int lineX = x + 50;
        int lineWidth = (i == 0) ? 200 : 150; // First line (name) is wider
        DrawRect(lineX, textY + i * lineHeight, lineWidth, 20, m_textColor, true);
    }
}

void UI::RenderMainMenu() {
    int menuWidth = 300;
    int menuHeight = 400;
    int x = 50;
    int y = 100;
    
    // Background
    DrawRect(x, y, menuWidth, menuHeight, m_bgColor, true);
    
    // Border
    SDL_Rect border = {x, y, menuWidth, menuHeight};
    SDL_SetRenderDrawColor(m_renderer, m_accentColor.r, m_accentColor.g, m_accentColor.b, 255);
    SDL_RenderDrawRect(m_renderer, &border);
    
    // Menu items (simplified)
    int itemY = y + 40;
    int itemHeight = 40;
    int itemSpacing = 10;
    
    std::vector<std::string> menuItems = {
        "Load APK",
        "Installed APKs",
        "Settings",
        "About",
        "Exit"
    };
    
    for (size_t i = 0; i < menuItems.size(); ++i) {
        int itemX = x + 20;
        int itemWidth = menuWidth - 40;
        int currentY = itemY + i * (itemHeight + itemSpacing);
        
        // Menu item background
        DrawRect(itemX, currentY, itemWidth, itemHeight, {50, 50, 60, 255}, true);
        
        // Menu item indicator
        DrawRect(itemX + 5, currentY + 5, 5, itemHeight - 10, m_accentColor, true);
    }
}

void UI::RenderAPKList(const std::vector<std::string>& apkList) {
    // Render list of APKs
    int x = 400;
    int y = 100;
    int itemHeight = 30;
    
    for (size_t i = 0; i < apkList.size(); ++i) {
        int currentY = y + i * itemHeight;
        DrawRect(x, currentY, 400, itemHeight - 5, {40, 40, 50, 255}, true);
    }
}

bool UI::HandleClick(int x, int y) {
    // Handle mouse clicks on UI elements
    // This would be implemented based on UI state
    return false;
}

void UI::DrawText(const std::string& text, int x, int y, SDL_Color color) {
    // Placeholder for text rendering
    // In production, use SDL_ttf or similar
    (void)text;
    (void)x;
    (void)y;
    (void)color;
}

void UI::DrawRect(int x, int y, int w, int h, SDL_Color color, bool filled) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    
    if (filled) {
        SDL_RenderFillRect(m_renderer, &rect);
    } else {
        SDL_RenderDrawRect(m_renderer, &rect);
    }
}

void UI::DrawLine(int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
}
