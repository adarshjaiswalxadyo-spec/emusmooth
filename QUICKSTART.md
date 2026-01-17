# Quick Start Guide

Get up and running in 5 minutes!

---

## Prerequisites Check

Before building, ensure you have:

- [ ] **CMake** installed (`cmake --version`)
- [ ] **C++ Compiler** installed (`g++ --version` or `cl`)
- [ ] **SDL2** development libraries

---

## Fastest Build Path (MSYS2)

If you have MSYS2 installed:

```bash
# Install dependencies
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-SDL2

# Build
cd /c/Users/adars/OneDrive/Desktop/emulator
./build.sh Release

# Run
cd build/bin
./Emulator.exe
```

---

## Manual Build (Any Setup)

### 1. Install SDL2

**Option A: MSYS2** (Easiest)
```bash
pacman -S mingw-w64-x86_64-SDL2
```

**Option B: Manual Download**
1. Download from https://www.libsdl.org/download-2.0.php
2. Extract to `C:\SDL2`
3. Set `SDL2_DIR=C:\SDL2\cmake`

### 2. Build

```batch
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

### 3. Run

```batch
cd bin
Emulator.exe
```

---

## What You Should See

1. **Window opens** with title "Emulator - Built by Adarsh Jaiswal"
2. **FPS counter** in top-left corner (should show ~60 FPS)
3. **Main menu** on the left side
4. **Dark background** with content area

---

## Test Controls

- **F1**: Toggle debug overlay
- **F2**: Show about screen (with your info!)
- **F3**: Toggle main menu
- **ESC**: Quit

---

## Troubleshooting

### "SDL2 not found"
→ Install SDL2 (see above)

### "SDL2.dll missing"
→ Copy `SDL2.dll` to `build/bin/` folder

### Build fails
→ See `BUILD.md` for detailed troubleshooting

---

## Next Steps

- Read `README.md` for full documentation
- Check `ARCHITECTURE.md` for system design
- Customize `config.json` for settings
- Create installer: See `installer/installer.nsi`

---

**Ready to build?** Run `build.bat Release` and you're done! 🚀
