#!/bin/bash

# Nat20 RPG Dice Roller Build Script

set -e  # Exit on any error

echo "Building Nat20 Clipboard Manager..."

# Determine build type
BUILD_TYPE="Debug"
if [ "$1" == "y" ]; then
    BUILD_TYPE="Release"
    echo "Performing RELEASE build."
else
    echo "Performing DEBUG build (default)."
fi

# Check if build directory exists
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

echo "Building Windows EXE..."
# ./build-windows.sh

# Navigate to build directory
cd build

# Configure with CMake if needed
if [ ! -f "Makefile" ]; then
    echo "Configuring with CMake..."
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
fi

# Build the project
echo "Compiling..."
make

# Check if build was successful
if [ -f "bin/nat20" ]; then
    echo "-- Build successful --"
    echo "Executable: $(pwd)/bin/nat20"
    echo ""
    echo "To run nat20:"
    echo "  ./bin/nat20"
    echo ""
    echo "Or from the parent directory:"
    echo "  ./build/bin/nat20"
else
    echo "! failed !"
    exit 1
fi
