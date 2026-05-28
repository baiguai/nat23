#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BIN_DIR="$SCRIPT_DIR/build/bin/windows"
EXE="nat23.exe"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# -----------------------------
# Build configuration
# -----------------------------
BUILD_TYPE="debug"

if [[ "${1:-}" == "r" ]]; then
    BUILD_TYPE="release"
fi

echo -e "${YELLOW}==> Build type: $BUILD_TYPE${NC}"

CXX="x86_64-w64-mingw32-g++"
CC="x86_64-w64-mingw32-gcc"

BASE_FLAGS=""

if [[ "$BUILD_TYPE" == "release" ]]; then
    OPT_FLAGS="-O3 -DNDEBUG"
else
    OPT_FLAGS="-O0 -g"
fi

CXXFLAGS="-std=c++17 $BASE_FLAGS $OPT_FLAGS"
CFLAGS="$OPT_FLAGS"

CXXFLAGS_STATIC="-static-libstdc++ -static-libgcc"

SOURCES=(
    "src/main.cpp"
)

echo -e "${YELLOW}==> Checking for MinGW-w64...${NC}"
if ! command -v "$CXX" &>/dev/null; then
    echo -e "${RED}$CXX not found. Install it with:${NC}"
    echo "  sudo apt install mingw-w64"
    echo ""
    read -rp "Install mingw-w64 now? [y/N] " answer
    if [[ "$answer" =~ ^[Yy]$ ]]; then
        sudo apt install -y mingw-w64
    else
        echo "Aborting."
        exit 1
    fi
fi

echo -e "${YELLOW}==> Compiling...${NC}"
mkdir -p "$BIN_DIR"
FULL_EXE="$BIN_DIR/$EXE"
OBJS=()
for src in "${SOURCES[@]}"; do
    base="$(basename "$src")"
    obj="$BIN_DIR/${base%.*}.o"
    ext="${src##*.}"
    if [[ "$ext" == "c" ]]; then
        echo "  $CC -c $src"
        $CC $CFLAGS -c "$src" -o "$obj"
    else
        echo "  $CXX -c $src"
        $CXX $CXXFLAGS $CXXFLAGS_STATIC -c "$src" -o "$obj"
    fi
    OBJS+=("$obj")
done

echo -e "${YELLOW}==> Linking...${NC}"
$CXX $CXXFLAGS_STATIC -o "$FULL_EXE" "${OBJS[@]}"

echo -e "${YELLOW}==> Cleaning up .o files...${NC}"
rm -f "${OBJS[@]}"

echo -e "${GREEN}==> Done: $FULL_EXE${NC}"
echo -e "${GREEN}    (copy the whole bin/windows/ folder to a Windows machine to run)${NC}"
