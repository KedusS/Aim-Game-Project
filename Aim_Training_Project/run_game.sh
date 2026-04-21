#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$ROOT_DIR/final_project"
BUILD_DIR="$PROJECT_DIR/build2"
GAME_BIN="$BUILD_DIR/game"

configure_build() {
    cmake -S "$PROJECT_DIR" -B "$BUILD_DIR" \
        -DSDL2_INCLUDE_DIR=/usr/local/opt/sdl2/include/SDL2 \
        -DSDL2_IMAGE_INCLUDE_DIR=/usr/local/opt/sdl2_image/include/SDL2 \
        -DSDL2_IMAGE_LIBRARY=/usr/local/opt/sdl2_image/lib/libSDL2_image.dylib \
        -DSDL2_MIXER_INCLUDE_DIR=/usr/local/opt/sdl2_mixer/include/SDL2 \
        -DSDL2_TTF_INCLUDE_DIR=/usr/local/opt/sdl2_ttf/include/SDL2
}

build_game() {
    configure_build
    cmake --build "$BUILD_DIR" --target game --parallel "${BUILD_JOBS:-2}"
}

find_libavif15_dir() {
    if [[ -e /usr/local/opt/libavif/lib/libavif.15.dylib ]]; then
        printf '%s\n' "/usr/local/opt/libavif/lib"
        return 0
    fi

    local match
    match="$(find /usr/local/Cellar/libavif -path '*/lib/libavif.15*.dylib' 2>/dev/null | sort | tail -n 1 || true)"
    if [[ -n "$match" ]]; then
        dirname "$match"
        return 0
    fi

    return 1
}

if [[ "${1:-}" == "--build" || ! -x "$GAME_BIN" ]]; then
    build_game
fi

if libavif_dir="$(find_libavif15_dir)"; then
    export DYLD_LIBRARY_PATH="$libavif_dir${DYLD_LIBRARY_PATH:+:$DYLD_LIBRARY_PATH}"
else
    cat <<'EOF' >&2
Missing libavif.15.dylib.
Quick fix: brew reinstall sdl2_image
Then rerun ./run_game.sh
EOF
    exit 1
fi

exec "$GAME_BIN"
