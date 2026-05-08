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
echo "Starting Nat20..."
echo "--==[ Clipboard Manager Features ]==--"
echo "  • Press Ctrl+Alt+C to show window"
echo "  • Press ? for help dialog"
echo "  • Press Shift+M for bookmark management"
echo "  • Press / to filter clipboard items"
echo "  • Press Escape to hide window"
echo "  • Press Shift+Q to quit"
echo ""
echo ">> Hotkey: Ctrl+Alt+C (fallback: Ctrl+Alt+V)"
echo ">> Config: ~/.config/nat20"
echo ""
echo "Starting application..."
echo "----------------------------------------"
echo ""
echo ""

# Run the application
./build/bin/nat20
