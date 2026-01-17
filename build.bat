@echo off
REM Build script for Windows
REM Usage: build.bat [Debug|Release]

set BUILD_TYPE=Release
if "%1"=="Debug" set BUILD_TYPE=Debug
if "%1"=="debug" set BUILD_TYPE=Debug

echo Building %BUILD_TYPE% configuration...

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake
echo Configuring CMake...
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..

if errorlevel 1 (
    echo CMake configuration failed!
    echo Trying Visual Studio generator...
    cmake -G "Visual Studio 17 2022" -A x64 ..
    if errorlevel 1 (
        echo CMake configuration failed with both generators!
        pause
        exit /b 1
    )
)

REM Build
echo Building project...
cmake --build . --config %BUILD_TYPE%

if errorlevel 1 (
    echo Build failed!
    cd ..
    pause
    exit /b 1
)

echo.
echo Build successful!
echo Executable location: build\bin\%PROJECT_NAME%.exe
echo.
cd ..
pause
