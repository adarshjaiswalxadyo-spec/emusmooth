# Build Instructions

Detailed step-by-step guide for building the Emulator on Windows.

---

## Prerequisites

### 1. Install CMake
- Download from: https://cmake.org/download/
- Version: 3.15 or higher
- Add to PATH during installation

### 2. Install C++ Compiler

#### Option A: MinGW-w64 (Recommended for beginners)
- **MSYS2** (Recommended):
  1. Download from: https://www.msys2.org/
  2. Install MSYS2
  3. Open MSYS2 terminal and run:
     ```bash
     pacman -Syu
     pacman -S mingw-w64-x86_64-gcc
     pacman -S mingw-w64-x86_64-cmake
     pacman -S mingw-w64-x86_64-SDL2
     ```
  4. Add `C:\msys64\mingw64\bin` to PATH

- **Standalone MinGW-w64**:
  1. Download from: https://www.mingw-w64.org/downloads/
  2. Extract to `C:\mingw64`
  3. Add `C:\mingw64\bin` to PATH

#### Option B: Visual Studio (MSVC)
- Download Visual Studio 2019 or 2022 (Community Edition is free)
- Install "Desktop development with C++" workload
- Includes MSVC compiler and CMake support

### 3. Install SDL2

#### For MinGW-w64 (via MSYS2)
```bash
pacman -S mingw-w64-x86_64-SDL2
```

#### For MinGW-w64 (Manual)
1. Download SDL2-devel from: https://www.libsdl.org/download-2.0.php
2. Extract to `C:\SDL2`
3. Set environment variable: `SDL2_DIR=C:\SDL2\cmake`

#### For MSVC
1. Download SDL2-devel from: https://www.libsdl.org/download-2.0.php
2. Extract to `C:\SDL2`
3. Set environment variable: `SDL2_DIR=C:\SDL2\cmake`

---

## Building

### Method 1: Using Build Scripts (Easiest)

#### Windows Command Prompt
```batch
build.bat Release
```

#### Git Bash / MSYS2
```bash
chmod +x build.sh
./build.sh Release
```

### Method 2: Manual CMake Build

#### Step 1: Create Build Directory
```batch
mkdir build
cd build
```

#### Step 2: Configure CMake

**For MinGW-w64:**
```batch
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
```

**For Visual Studio:**
```batch
cmake -G "Visual Studio 17 2022" -A x64 ..
```

#### Step 3: Build
```batch
cmake --build . --config Release
```

**For MinGW (make):**
```batch
mingw32-make
```

---

## Build Output

After successful build:

```
build/
└── bin/
    ├── Emulator.exe      # Main executable
    ├── SDL2.dll          # SDL2 runtime (copied automatically)
    └── assets/           # Assets folder (copied automatically)
```

---

## Testing the Build

1. Navigate to build directory:
   ```batch
   cd build\bin
   ```

2. Run the executable:
   ```batch
   Emulator.exe
   ```

3. You should see:
   - Window opens with title "Emulator - Built by Adarsh Jaiswal"
   - FPS counter in top-left
   - Main menu visible
   - Press F1 for debug overlay
   - Press F2 for about screen

---

## Debug Build

To build with debug symbols:

```batch
build.bat Debug
```

Or manually:
```batch
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug
```

---

## Troubleshooting

### CMake can't find SDL2

**Error**: `Could NOT find SDL2`

**Solutions**:
1. **MSYS2**: Ensure SDL2 is installed: `pacman -S mingw-w64-x86_64-SDL2`
2. **Manual**: Set `SDL2_DIR` environment variable:
   ```batch
   set SDL2_DIR=C:\SDL2\cmake
   ```
3. **Check installation**: Verify SDL2Config.cmake exists in SDL2 directory

### Missing SDL2.dll

**Error**: `The program can't start because SDL2.dll is missing`

**Solutions**:
1. Check that DLL copy command ran in CMake
2. Manually copy `SDL2.dll` to `build/bin/`
3. For MSYS2: Copy from `C:\msys64\mingw64\bin\SDL2.dll`

### Compiler not found

**Error**: `No CMAKE_CXX_COMPILER could be found`

**Solutions**:
1. Ensure compiler is in PATH
2. For MinGW: Add `C:\mingw64\bin` or `C:\msys64\mingw64\bin` to PATH
3. Restart terminal after adding to PATH
4. Verify: `g++ --version` or `cl`

### JSON library download fails

**Error**: `Failed to fetch json`

**Solutions**:
1. Check internet connection (CMake downloads nlohmann/json from GitHub)
2. If behind proxy, configure Git/CMake proxy settings
3. Alternative: Manually download and place in `third_party/json/`

### Link errors

**Error**: Various linker errors

**Solutions**:
1. Ensure SDL2 libraries are properly linked
2. Check that all source files are included in CMakeLists.txt
3. Clean build: Delete `build/` folder and rebuild

---

## Creating Portable Build

To create a portable build that runs on other PCs:

1. Build Release configuration
2. Copy entire `build/bin/` folder
3. Ensure it contains:
   - `Emulator.exe`
   - `SDL2.dll`
   - `assets/` folder
4. Test on another PC (without SDL2 installed)

---

## Next Steps

- See `README.md` for usage instructions
- See `installer/installer.nsi` for creating installer
- Customize `config.json` for settings

---

**Need Help?**  
Contact: [@adar.xhevil](https://www.instagram.com/adar.xhevil/)
