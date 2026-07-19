#!/usr/bin/env bash
set -e

########################################
# Directories
########################################

ROOT="$(pwd)"

RAYLIB_SRC="$ROOT/third_party/raylib"
BUILD="$RAYLIB_SRC/build"

LIB_OUT="$ROOT/lib"
INC_OUT="$ROOT/include/raylib"

DATA_LIB_OUT="$ROOT/data/libs"
DATA_INC_OUT="$ROOT/data/include"

########################################
# Clone / Update
########################################

if [ ! -d "$RAYLIB_SRC/.git" ]; then
    git clone https://github.com/raysan5/raylib.git "$RAYLIB_SRC"
else
    git -C "$RAYLIB_SRC" pull
fi

########################################
# Clean
########################################

rm -rf "$BUILD"

mkdir -p "$BUILD"

mkdir -p "$LIB_OUT"
mkdir -p "$INC_OUT"

mkdir -p "$DATA_LIB_OUT"
mkdir -p "$DATA_INC_OUT"

########################################
# Configure
########################################

cd "$BUILD"

cmake .. \
    -DBUILD_SHARED_LIBS=ON \
    -DBUILD_EXAMPLES=OFF \
    -DCMAKE_BUILD_TYPE=Release

########################################
# Build
########################################

cmake --build . --config Release

########################################
# Copy headers
########################################

echo "Copying headers..."

cp "$RAYLIB_SRC/src/"*.h "$INC_OUT/"
cp "$RAYLIB_SRC/src/"*.h "$DATA_INC_OUT/"

########################################
# Copy Windows files
########################################

echo "Copying Windows libraries..."

find "$BUILD" -name "raylib.dll" \
    -exec cp {} "$ROOT/" \;

find "$BUILD" -name "libraylib.dll.a" \
    -exec cp {} "$LIB_OUT/" \;

find "$BUILD" -name "libraylib.dll.a" \
    -exec cp {} "$DATA_LIB_OUT/" \;

find "$BUILD" -name "raylib.lib" \
    -exec cp {} "$LIB_OUT/" \;

find "$BUILD" -name "raylib.lib" \
    -exec cp {} "$DATA_LIB_OUT/" \;

########################################
# Copy Linux files
########################################

echo "Copying Linux libraries..."

find "$BUILD" -name "libraylib.so*" \
    -exec cp {} "$LIB_OUT/" \;

find "$BUILD" -name "libraylib.so*" \
    -exec cp {} "$DATA_LIB_OUT/" \;

if [ -f "$LIB_OUT/libraylib.so" ]; then
    cp "$LIB_OUT/libraylib.so" "$ROOT/"
fi

########################################

echo
echo "======================================"
echo "Raylib updated successfully."
echo "======================================"