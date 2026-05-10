#!/bin/bash

# Nat20 Dice Roller Run Script

set -e  # Exit on any error

echo "...Starting Nat20 Dice Roller..."

# First build the application
echo "Building Nat20..."
./build.sh

# Check if build was successful
if [ ! -f "build/bin/nat20" ]; then
    echo "! Build failed ! -- Cannot start Nat20."
    exit 1
fi

echo "-- Build successful --"
echo ""
echo ""

# Run the application
./build/bin/nat20
