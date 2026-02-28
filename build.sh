#!/usr/bin/env bash
# ------------------------------------------------------------------
# build.sh — Self-contained build for TreeMaker on macOS.
#
# Downloads and compiles wxWidgets locally (in deps/) if needed,
# then builds TreeMaker against it. Nothing is installed system-wide.
#
# Usage:
#   ./build.sh                 # Debug build (default)
#   ./build.sh Release         # Release build
#   ./build.sh clean           # Remove build artifacts (keeps deps)
#   ./build.sh clean-all       # Remove everything including deps
#
# Prerequisites: Xcode Command Line Tools, cmake
#   xcode-select --install
#   brew install cmake         (or any other way to get cmake ≥ 3.15)
# ------------------------------------------------------------------
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
DEPS_DIR="${ROOT_DIR}/deps"
WX_VERSION="3.2.7"
WX_SRC_DIR="${DEPS_DIR}/wxWidgets-${WX_VERSION}"
WX_BUILD_DIR="${DEPS_DIR}/wxWidgets-build"
WX_INSTALL_DIR="${DEPS_DIR}/wxWidgets-install"
BUILD_TYPE="${1:-Debug}"
BUILD_DIR="${ROOT_DIR}/build"
NPROC="$(sysctl -n hw.ncpu 2>/dev/null || echo 4)"

# ---- Handle clean targets ----
if [[ "${BUILD_TYPE}" == "clean" ]]; then
    echo "==> Removing build directory…"
    rm -rf "${BUILD_DIR}"
    echo "Done."
    exit 0
fi
if [[ "${BUILD_TYPE}" == "clean-all" ]]; then
    echo "==> Removing build and deps directories…"
    rm -rf "${BUILD_DIR}" "${DEPS_DIR}"
    echo "Done."
    exit 0
fi

# ---- Check prerequisites ----
if ! command -v cmake &>/dev/null; then
    echo "Error: cmake not found. Install it with: brew install cmake" >&2
    exit 1
fi
if ! command -v clang++ &>/dev/null; then
    echo "Error: clang++ not found. Install Xcode CLT: xcode-select --install" >&2
    exit 1
fi

# ---- Determine SDK & deployment target ----
SDK_PATH="$(xcrun --show-sdk-path 2>/dev/null)"
MACOS_VERSION="$(sw_vers -productVersion | cut -d. -f1)"
# Use 13.3 (Ventura) as minimum — required for std::to_chars (floating point)
# which C++20 <format> depends on
DEPLOY_TARGET="13.3"
ARCH="$(uname -m)"   # arm64 or x86_64

echo "==> macOS ${MACOS_VERSION}, SDK: ${SDK_PATH}, arch: ${ARCH}"
echo "==> Deployment target: ${DEPLOY_TARGET}"

# ---- Download wxWidgets if needed ----
if [[ ! -f "${WX_INSTALL_DIR}/bin/wx-config" ]]; then
    mkdir -p "${DEPS_DIR}"

    if [[ ! -d "${WX_SRC_DIR}" ]]; then
        WX_TARBALL="${DEPS_DIR}/wxWidgets-${WX_VERSION}.tar.bz2"
        if [[ ! -f "${WX_TARBALL}" ]]; then
            echo "==> Downloading wxWidgets ${WX_VERSION}…"
            curl -L -o "${WX_TARBALL}" \
                "https://github.com/wxWidgets/wxWidgets/releases/download/v${WX_VERSION}/wxWidgets-${WX_VERSION}.tar.bz2"
        fi
        echo "==> Extracting wxWidgets…"
        tar xjf "${WX_TARBALL}" -C "${DEPS_DIR}"
    fi

    echo "==> Building wxWidgets ${WX_VERSION} (this takes a few minutes)…"
    mkdir -p "${WX_BUILD_DIR}"
    cd "${WX_BUILD_DIR}"

    # Create a shim for fp.h — removed from modern macOS SDKs but
    # still referenced by the bundled libpng in wxWidgets 3.2.x
    mkdir -p "${WX_BUILD_DIR}/shim"
    cat > "${WX_BUILD_DIR}/shim/fp.h" << 'SHIMEOF'
/* fp.h shim — this header was removed in recent macOS SDKs.
   The bundled libpng only used it for __nan() on old 32-bit Mac,
   which is irrelevant on modern 64-bit builds. */
#include <math.h>
SHIMEOF

    "${WX_SRC_DIR}/configure" \
        --srcdir="${WX_SRC_DIR}" \
        --prefix="${WX_INSTALL_DIR}" \
        --with-osx_cocoa \
        --with-macosx-version-min="${DEPLOY_TARGET}" \
        --with-macosx-sdk="${SDK_PATH}" \
        --enable-unicode \
        --enable-stl \
        --enable-std_containers \
        --enable-std_string \
        --disable-shared \
        --enable-monolithic \
        --with-libjpeg=builtin \
        --with-libpng=builtin \
        --with-libtiff=builtin \
        --with-zlib=sys \
        --with-expat=builtin \
        CXX="clang++" \
        CXXFLAGS="-std=c++17 -arch ${ARCH} -I${WX_BUILD_DIR}/shim" \
        CC="clang" \
        CFLAGS="-arch ${ARCH} -I${WX_BUILD_DIR}/shim" \
        LDFLAGS="-arch ${ARCH}"

    make -j"${NPROC}"
    make install

    cd "${ROOT_DIR}"
    echo "==> wxWidgets installed to ${WX_INSTALL_DIR}"
fi

# ---- Configure TreeMaker ----
echo "==> Configuring TreeMaker (${BUILD_TYPE})…"
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

# Clear stale CMake cache to avoid SDK/compiler mismatch after OS upgrades
if [[ -f CMakeCache.txt ]]; then
    cached_sdk="$(grep -m1 'CMAKE_OSX_SYSROOT' CMakeCache.txt 2>/dev/null | cut -d= -f2 || true)"
    if [[ -n "${cached_sdk}" && ! -d "${cached_sdk}" ]]; then
        echo "==> Stale SDK path in cache (${cached_sdk}), reconfiguring…"
        rm -f CMakeCache.txt
        rm -rf CMakeFiles
    fi
fi

# Point cmake at our local wxWidgets via wx-config
export PATH="${WX_INSTALL_DIR}/bin:${PATH}"

cmake "${ROOT_DIR}" \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET="${DEPLOY_TARGET}" \
    -DCMAKE_OSX_ARCHITECTURES="${ARCH}" \
    -DCMAKE_OSX_SYSROOT="${SDK_PATH}" \
    -DwxWidgets_CONFIG_EXECUTABLE="${WX_INSTALL_DIR}/bin/wx-config"

# ---- Build ----
echo "==> Building TreeMaker…"
cmake --build . -j"${NPROC}"

echo ""
echo "==> Build complete!"
echo "    App: ${BUILD_DIR}/bin/TreeMaker.app"
echo "    Run: open ${BUILD_DIR}/bin/TreeMaker.app"
