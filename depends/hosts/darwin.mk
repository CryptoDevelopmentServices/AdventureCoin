# --------------------------------------------------------------------
# darwin.mk — patched for macOS 10.12 / Darwin16
# Works with osxcross + ld64 253.3 + SDK 10.12
# --------------------------------------------------------------------

OSX_MIN_VERSION=10.12
OSX_SDK_VERSION=10.12
OSX_SDK=$(SDK_PATH)/MacOSX$(OSX_SDK_VERSION).sdk

# must match ld64 bundled in osxcross + Xcode 7.3.1
LD64_VERSION=253.3

# Compiler + linker configuration for cross-compiling to macOS
darwin_CC=clang -target $(host) \
    -mmacosx-version-min=$(OSX_MIN_VERSION) \
    --sysroot $(OSX_SDK) \
    -mlinker-version=$(LD64_VERSION)

darwin_CXX=clang++ -target $(host) \
    -mmacosx-version-min=$(OSX_MIN_VERSION) \
    --sysroot $(OSX_SDK) \
    -mlinker-version=$(LD64_VERSION) \
    -stdlib=libc++

# Base CFLAGS
darwin_CFLAGS=-pipe
darwin_CXXFLAGS=$(darwin_CFLAGS)

# Optimized build
darwin_release_CFLAGS=-O2
darwin_release_CXXFLAGS=$(darwin_release_CFLAGS)

# Debug build
darwin_debug_CFLAGS=-O1
darwin_debug_CXXFLAGS=$(darwin_debug_CFLAGS)

# Use native cctools (patched in CI)
darwin_native_toolchain=native_cctools

# Additional linker flags required for macOS < 10.12 compatibility
darwin_LDFLAGS=-Wl,-dead_strip \
    -mmacosx-version-min=$(OSX_MIN_VERSION) \
    -Wl,-syslibroot,$(OSX_SDK) \
    -Wl,-platform_version,macos,$(OSX_MIN_VERSION),$(OSX_SDK_VERSION)

# Export settings so all Depends packages inherit them
export CC=$(darwin_CC)
export CXX=$(darwin_CXX)
export CFLAGS=$(darwin_CFLAGS)
export CXXFLAGS=$(darwin_CXXFLAGS)
export LDFLAGS=$(darwin_LDFLAGS)
