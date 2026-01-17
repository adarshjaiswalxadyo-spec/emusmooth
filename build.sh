#!/bin/bash
# Build script for Windows (Git Bash/MSYS2)
# Usage: ./build.sh [Debug|Release]

BUILD_TYPE=${1:-Release}

if [ "$BUILD_TYPE" != "Debug" ] && [ "$BUILD_TYPE" != "Release" ]; then
    echo "Usage: $0 [Debug|Release]"
    exit 1
fi

echo "Building $BUILD_TYPE configuration..."

# Create build directory
mkdir -p build
cd build

# Configure with CMake
echo "Configuring CMake..."
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# Build
echo "Building project..."
cmake --build . --config $BUILD_TYPE

if [ $? -ne 0 ]; then
    echo "Build failed!"
    cd ..
    exit 1
fi

echo ""
echo "Build successful!"
echo "Executable location: build/bin/Emulator.exe"
echo ""
cd ..
