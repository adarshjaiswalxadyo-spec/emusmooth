# GitHub Actions CI/CD Setup

This project is configured to build automatically on GitHub Actions.

## Workflow

The workflow file is located at: `.github/workflows/build.yml`

### What It Does

1. **Checks out** the repository
2. **Downloads and installs** SDL2 for MSVC
3. **Configures** CMake with Visual Studio 2022
4. **Builds** Release configuration
5. **Packages** Emulator.exe with SDL2.dll
6. **Uploads** artifact as `Emulator-Windows.zip`

### Triggering the Build

The workflow runs automatically on:
- **Push** to `main` or `master` branch
- **Pull requests** to `main` or `master` branch
- **Manual trigger** via "Run workflow" button in Actions tab

### Downloading the Build

1. Go to **Actions** tab in GitHub
2. Click on the latest workflow run
3. Scroll down to **Artifacts** section
4. Download **Emulator-Windows** artifact
5. Extract the ZIP file
6. Run `Emulator.exe`

### Artifact Contents

```
Emulator-Windows.zip
├── Emulator.exe
├── SDL2.dll
├── assets/ (if present)
└── config.json.template
```

## Requirements

- Repository structure must match exactly (CMakeLists.txt at root)
- All source files in `src/` and `include/`
- No hardcoded paths in CMakeLists.txt

## Troubleshooting

### Build Fails: "SDL2 not found"

- Check that SDL2 download URL is correct in workflow
- Verify SDL2_DIR is set correctly
- Check workflow logs for SDL2 extraction path

### Build Fails: "Emulator.exe not found"

- Check that CMake configuration succeeded
- Verify build completed without errors
- Check that executable is in expected location (build/Release/ or build/bin/)

### DLL Missing in Artifact

- Workflow should copy SDL2.dll automatically
- Check workflow logs for DLL copy step
- Verify SDL2 package contains SDL2.dll

---

**Note**: The workflow uses MSVC (Visual Studio 2022) on `windows-latest` runner.
