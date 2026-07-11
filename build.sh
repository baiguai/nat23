#!/bin/bash

# Nat20 RPG Dice Roller Build Script

set -e  # Exit on any error

echo "Building Nat20 Clipboard Manager..."

# Determine build type
BUILD_TYPE="Debug"
if [ "$1" == "r" ]; then
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

# Navigate to build directory
cd build

# Configure with CMake if needed
if [ ! -f "Makefile" ]; then
    echo "Configuring with CMake..."
    CXX_COMPILER="g++"
    if command -v g++-13 &>/dev/null; then
        CXX_COMPILER="g++-13"
    elif command -v g++-14 &>/dev/null; then
        CXX_COMPILER="g++-14"
    fi
    echo "Using compiler: $CXX_COMPILER"
    cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_CXX_COMPILER=$CXX_COMPILER ..
fi

# Build the project
echo "Compiling..."
make

# Check if build was successful
if [ -f "bin/nat23" ]; then
    echo "-- Build successful --"
    echo "Executable: $(pwd)/bin/nat23"
    echo ""
    echo "To run nat23:"
    echo "  ./bin/nat23"
    echo ""
    echo "Or from the parent directory:"
    echo "  ./build/bin/nat23"
else
    echo "! failed !"
    exit 1
fi
