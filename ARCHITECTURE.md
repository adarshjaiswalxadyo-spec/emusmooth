# Architecture Documentation

## Overview

The Emulator is a Windows C++ application built with SDL2 for rendering and input handling. It provides a framework for emulation with APK support capabilities.

---

## System Architecture

### Core Components

```
┌─────────────────────────────────────────┐
│           Main Application              │
│  (main.cpp → Emulator class)            │
└─────────────────┬───────────────────────┘
                  │
      ┌───────────┴───────────┐
      │                       │
┌─────▼──────┐        ┌──────▼──────┐
│   SDL2     │        │   Config    │
│  Rendering │        │  Manager    │
└────────────┘        └─────────────┘
      │                       │
      │              ┌────────┴────────┐
      │              │                 │
┌─────▼──────┐  ┌────▼─────┐   ┌──────▼──────┐
│     UI     │  │   Key    │   │     APK     │
│  Manager   │  │  Mapper  │   │   Manager   │
└────────────┘  └──────────┘   └─────────────┘
```

---

## Component Details

### 1. Emulator (Core Engine)

**File**: `src/Emulator.cpp`, `include/Emulator.h`

**Responsibilities**:
- Main application loop
- SDL2 initialization and cleanup
- Frame pacing and FPS tracking
- Event processing
- Component coordination

**Key Features**:
- **Frame Pacing**: Targets 60 FPS with frame time limiting
- **VSync**: Uses SDL_RENDERER_PRESENTVSYNC for smooth rendering
- **FPS Counter**: Real-time FPS calculation and display
- **State Management**: Handles UI states (menu, about, debug overlay)

**Main Loop**:
```cpp
while (running) {
    CalculateDeltaTime();
    LimitFrameRate();  // Frame pacing
    ProcessEvents();
    Update(deltaTime);
    Render();
    PresentFrame();
}
```

---

### 2. ConfigManager

**File**: `src/ConfigManager.cpp`, `include/ConfigManager.h`

**Responsibilities**:
- JSON configuration file management
- Settings persistence
- Default configuration creation

**Features**:
- Load/save JSON config files
- Type-safe getters/setters (string, int, float, bool)
- Window settings management
- Automatic default creation

**Config Structure**:
```json
{
    "window_width": 1280,
    "window_height": 720,
    "fullscreen": false,
    "vsync": true,
    "target_fps": 60
}
```

---

### 3. KeyMapper

**File**: `src/KeyMapper.cpp`, `include/KeyMapper.h`

**Responsibilities**:
- Keyboard input mapping
- Action-to-key binding
- Key mapping persistence (via ConfigManager)

**Features**:
- Map SDL scancodes to action strings
- Default key bindings
- Load/save mappings from config

**Default Mappings**:
- `ESC` → Quit
- `F1` → Toggle debug overlay
- `F2` → Toggle about screen
- `F3` → Toggle main menu
- `F11` → Toggle fullscreen

---

### 4. APKManager

**File**: `src/APKManager.cpp`, `include/APKManager.h`

**Responsibilities**:
- APK file management
- APK installation simulation
- Installed APK tracking

**Features**:
- Load APK files
- Extract APK metadata (simplified)
- Maintain installed APK list
- Launch APK (simulated)

**Limitations**:
⚠️ **Current Implementation**: Simulated launcher only
- Does NOT execute APK files
- Does NOT parse AndroidManifest.xml
- Requires external Android runtime for actual execution

**Future Integration**:
- APK extraction (ZIP parsing)
- AndroidManifest.xml parsing
- Integration with Android-x86, Anbox, or similar runtime
- Container/VM execution

---

### 5. UI (User Interface)

**File**: `src/UI.cpp`, `include/UI.h`

**Responsibilities**:
- UI rendering
- Screen management
- Visual feedback

**Features**:
- FPS counter display
- Debug overlay
- About screen
- Main menu
- APK list display

**Current Implementation**:
- Uses SDL2 primitives (rectangles, lines)
- No text rendering (would require SDL_ttf)
- Placeholder UI elements

**Future Enhancements**:
- SDL_ttf integration for text rendering
- More polished UI design
- Settings screen
- APK selection dialog

---

## Data Flow

### Application Startup
```
main()
  └─> Emulator::Initialize()
       ├─> SDL_Init()
       ├─> ConfigManager::LoadConfig()
       ├─> SDL_CreateWindow()
       ├─> SDL_CreateRenderer()
       ├─> KeyMapper::SetDefaultMappings()
       └─> UI initialization
```

### Main Loop
```
Emulator::Run()
  └─> Loop:
       ├─> Calculate deltaTime
       ├─> Frame pacing (limit to 60 FPS)
       ├─> ProcessEvents()
       │    └─> SDL_PollEvent()
       │         └─> Handle keyboard/mouse/window events
       ├─> Update(deltaTime)
       │    └─> Update emulator state
       ├─> Render()
       │    ├─> Clear screen
       │    ├─> Render main content
       │    ├─> Render UI overlays
       │    └─> Render FPS counter
       └─> SDL_RenderPresent()
```

### Shutdown
```
Emulator::Shutdown()
  ├─> ConfigManager::SaveConfig()
  ├─> SDL_DestroyRenderer()
  ├─> SDL_DestroyWindow()
  └─> SDL_Quit()
```

---

## Build System

### CMake Structure

**CMakeLists.txt**:
- C++17 standard
- SDL2 dependency (find_package)
- nlohmann/json (FetchContent)
- Automatic DLL copying (Windows)
- Asset copying
- Debug/Release configurations

**Build Process**:
1. CMake configuration
2. Fetch nlohmann/json (if needed)
3. Find SDL2
4. Generate build files
5. Compile source files
6. Link libraries
7. Copy DLLs and assets (post-build)

---

## File Structure

```
emulator/
├── CMakeLists.txt          # Build configuration
├── src/                    # Source files
│   ├── main.cpp           # Entry point
│   ├── Emulator.cpp       # Core engine
│   ├── ConfigManager.cpp  # Config management
│   ├── KeyMapper.cpp      # Input mapping
│   ├── APKManager.cpp     # APK handling
│   └── UI.cpp             # UI rendering
├── include/                # Headers
│   ├── Emulator.h
│   ├── ConfigManager.h
│   ├── KeyMapper.h
│   ├── APKManager.h
│   └── UI.h
├── assets/                 # Resources
├── installer/              # NSIS scripts
└── build/                  # Build output
    └── bin/
        ├── Emulator.exe
        ├── SDL2.dll
        └── assets/
```

---

## Dependencies

### External Libraries

1. **SDL2** (Simple DirectMedia Layer)
   - Purpose: Window management, rendering, input
   - Version: 2.x
   - License: zlib

2. **nlohmann/json**
   - Purpose: JSON parsing and generation
   - Version: 3.11.2
   - License: MIT
   - Type: Header-only

### System Requirements

- **OS**: Windows 10/11 (x64)
- **Compiler**: GCC 7+ (MinGW-w64) or MSVC 2019+
- **CMake**: 3.15+
- **Runtime**: SDL2.dll

---

## Design Patterns

### 1. RAII (Resource Acquisition Is Initialization)
- SDL resources managed in constructor/destructor
- Automatic cleanup on object destruction

### 2. Component-Based Architecture
- Separate managers for different concerns
- Loose coupling between components

### 3. Configuration-Driven
- Settings loaded from JSON
- No hardcoded values

---

## Performance Considerations

### Frame Pacing
- Target: 60 FPS
- Method: Frame time limiting + VSync
- Prevents frame stutter

### Memory Management
- Smart pointers for component management
- RAII for resource cleanup
- Minimal dynamic allocation

### Rendering
- GPU-accelerated SDL renderer
- VSync enabled for smooth frame delivery
- Efficient rectangle/line drawing

---

## Future Enhancements

### Short Term
- [ ] SDL_ttf integration for text rendering
- [ ] Improved UI design
- [ ] Settings screen
- [ ] APK file dialog

### Medium Term
- [ ] APK extraction and parsing
- [ ] AndroidManifest.xml parser
- [ ] Better APK metadata display

### Long Term
- [ ] Android runtime integration
- [ ] Full APK execution support
- [ ] Performance profiling tools
- [ ] Plugin system

---

## Security Considerations

### Current
- No network access
- No file system access beyond config/APK directories
- Input validation on config loading

### Future
- APK validation before installation
- Sandboxed APK execution
- Secure config file handling

---

## Legal & Compliance

### APK Support
- **No DRM bypass**: APK support is framework only
- **No APK cracking**: No reverse engineering tools
- **User responsibility**: Users must provide legal APKs
- **Documentation**: Clear limitations documented

### Dependencies
- All dependencies are open-source
- Licenses compatible with project goals

---

**Documentation Version**: 1.0.0  
**Last Updated**: 2024
