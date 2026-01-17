# Emulator - Windows C++ Emulator

A professional, ultra-smooth emulator for Windows built with C++17, SDL2, and CMake.

**Built by Adarsh Jaiswal**  
Web Developer  
Instagram: [@adar.xhevil](https://www.instagram.com/adar.xhevil/)

---

## Features

- ✅ Real-time FPS Counter
- ✅ Stable frame pacing (60 FPS target, no stutter)
- ✅ Custom key mapping system
- ✅ Config save/load (JSON)
- ✅ Minimal modern UI
- ✅ Debug overlay (toggleable with F1)
- ✅ About Developer screen (F2)
- ✅ APK support (simulated launcher)

---

## Requirements

### Build Tools
- **CMake** 3.15 or higher
- **C++ Compiler**: MinGW-w64 (GCC) OR MSVC (Visual Studio 2019+)
- **SDL2** development libraries

### Runtime
- Windows 10/11 (x64)
- SDL2.dll (included in build)

---

## Installation

### Option 1: Using Installer (Recommended)

1. Download `Emulator_Setup_1.0.0.exe`
2. Run the installer
3. Follow the installation wizard
4. Launch from desktop shortcut or Start Menu

### Option 2: Portable Build

1. Extract the build folder
2. Run `Emulator.exe` from the `bin` directory
3. Ensure `SDL2.dll` is in the same folder as the executable

---

## Building from Source

### Step 1: Install Dependencies

#### SDL2 (MinGW-w64)
```bash
# Using MSYS2
pacman -S mingw-w64-x86_64-SDL2

# Or download from https://www.libsdl.org/download-2.0.php
# Extract to C:\SDL2 or set SDL2_DIR environment variable
```

#### SDL2 (MSVC)
1. Download SDL2-devel from https://www.libsdl.org/download-2.0.php
2. Extract to `C:\SDL2`
3. Set environment variable: `SDL2_DIR=C:\SDL2\cmake`

### Step 2: Build

#### Using MinGW-w64 (Command Prompt)
```batch
build.bat Release
```

#### Using MinGW-w64 (Git Bash/MSYS2)
```bash
chmod +x build.sh
./build.sh Release
```

#### Using Visual Studio
```batch
mkdir build-vs
cd build-vs
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
```

### Step 3: Run
```batch
cd build\bin
Emulator.exe
```

---

## Build Output

After building, you'll find:
- **Executable**: `build/bin/Emulator.exe`
- **DLLs**: `build/bin/SDL2.dll` (copied automatically)
- **Assets**: `build/bin/assets/` (copied automatically)

---

## Creating Installer

### Prerequisites
1. Install [NSIS](https://nsis.sourceforge.io/Download)
2. Ensure `makensis.exe` is in your PATH

### Build Installer
```batch
cd installer
makensis installer.nsi
```

The installer will be created at: `build/Emulator_Setup_1.0.0.exe`

---

## Controls

| Key | Action |
|-----|--------|
| `ESC` | Quit / Close dialogs |
| `F1` | Toggle debug overlay |
| `F2` | Show/hide about screen |
| `F3` | Toggle main menu |
| `F11` | Toggle fullscreen (planned) |

---

## Configuration

Configuration is saved in `config.json` in the executable directory.

### Default Settings
```json
{
    "window_width": 1280,
    "window_height": 720,
    "fullscreen": false,
    "vsync": true,
    "target_fps": 60
}
```

Settings are automatically saved on exit.

---

## APK Support

### Current Implementation
The emulator includes a **simulated APK launcher** that:
- Allows APK file selection
- Maintains a list of installed APKs
- Provides a launch interface

### Limitations
⚠️ **Important**: This is a simulated launcher. Full APK execution requires:
- Android runtime (Android-x86, Anbox, or similar)
- APK parsing and extraction
- Container/VM execution environment

### How It Works
1. Place `.apk` files in the `apks/` directory
2. Use the "Load APK" option in the menu
3. Select an APK file to "install"
4. Launch from the installed APKs list

**Note**: Actual APK execution is not implemented. This is a framework for future integration with an Android runtime.

---

## Project Structure

```
emulator/
├── CMakeLists.txt          # Main CMake configuration
├── build.bat               # Windows build script
├── build.sh                # Unix-style build script
├── README.md               # This file
├── config.json.template    # Default configuration template
│
├── src/                    # Source files
│   ├── main.cpp
│   ├── Emulator.cpp
│   ├── ConfigManager.cpp
│   ├── KeyMapper.cpp
│   ├── APKManager.cpp
│   └── UI.cpp
│
├── include/                # Header files
│   ├── Emulator.h
│   ├── ConfigManager.h
│   ├── KeyMapper.h
│   ├── APKManager.h
│   └── UI.h
│
├── assets/                 # Assets (icons, fonts, etc.)
│
├── installer/              # NSIS installer scripts
│   ├── installer.nsi
│   └── license.txt
│
└── build/                  # Build output (generated)
    └── bin/
        └── Emulator.exe
```

---

## Troubleshooting

### CMake can't find SDL2

**Error**: `Could NOT find SDL2 (missing: SDL2_LIBRARY SDL2_INCLUDE_DIR)`

**Solutions**:
1. Install SDL2 development libraries
2. Set `SDL2_DIR` environment variable to SDL2 installation path
3. For MinGW: `pacman -S mingw-w64-x86_64-SDL2`
4. For MSVC: Download SDL2-devel and set `SDL2_DIR=C:\SDL2\cmake`

### Missing DLL errors

**Error**: `The program can't start because SDL2.dll is missing`

**Solutions**:
1. Ensure `SDL2.dll` is in the same folder as `Emulator.exe`
2. Check that CMake post-build copy commands ran successfully
3. Manually copy `SDL2.dll` from SDL2 installation to `build/bin/`

### Linker errors (SDL_main)

**Error**: `undefined reference to WinMain@16` or `SDL_main`

**Solution**: Ensure you're linking `SDL2::SDL2main` (handled automatically in CMakeLists.txt)

### Frame stutter / unstable FPS

**Solutions**:
1. Enable VSync in config: `"vsync": true`
2. Ensure GPU acceleration is enabled
3. Check that frame pacing code is working (target 60 FPS)
4. Disable other applications that might interfere

### Build fails with MinGW

**Error**: Various compilation errors

**Solutions**:
1. Update MinGW-w64 to latest version
2. Ensure C++17 support: `g++ --version` should show GCC 7+
3. Try Visual Studio generator instead: `cmake -G "Visual Studio 17 2022"`

### Installer doesn't create shortcuts

**Solution**: Run installer as Administrator

---

## Development

### Adding Features

1. **New UI Screen**: Add rendering code in `UI.cpp`
2. **New Config Option**: Add getter/setter in `ConfigManager.cpp`
3. **New Key Mapping**: Update `KeyMapper::SetDefaultMappings()`

### Debug Build

```batch
build.bat Debug
```

Debug builds include symbols and disable optimizations.

---

## License

This project is provided as-is for educational and personal use.

---

## Credits

**Developer**: Adarsh Jaiswal  
**Profession**: Web Developer  
**Instagram**: [@adar.xhevil](https://www.instagram.com/adar.xhevil/)

**Technologies Used**:
- C++17
- SDL2 (Simple DirectMedia Layer)
- CMake
- nlohmann/json
- NSIS (Installer)

---

## Support

For issues, questions, or contributions, please contact:
- Instagram: [@adar.xhevil](https://www.instagram.com/adar.xhevil/)

---

**Version**: 1.0.0  
**Last Updated**: 2024
