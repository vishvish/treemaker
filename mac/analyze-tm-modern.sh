#!/bin/bash

# Exit on error
set -e

# Create build directories
mkdir -p build/Release/TreeMaker.app/Contents/{MacOS,Resources,SharedSupport}

# Get wxWidgets flags
WX_CXXFLAGS=$(wx-config --cxxflags)
WX_LIBS=$(wx-config --libs)

# Additional include paths
INCLUDE_FLAGS="-I../Source -I../Source/about -I../Source/help -I../Source/images -I../Source/test \
              -I../Source/tmModel -I../Source/tmwxGUI -I../Source/test/tmModelTester \
              -I../Source/test/tmNLCOTester -I../Source/tmModel/tmNLCO \
              -I../Source/tmModel/tmOptimizers -I../Source/tmModel/tmPtrClasses \
              -I../Source/tmModel/tmSolvers -I../Source/tmModel/tmTreeClasses \
              -I../Source/tmModel/wnlib -I../Source/tmwxGUI/tmwxCommon \
              -I../Source/tmwxGUI/tmwxDocView -I../Source/tmwxGUI/tmwxFoldedForm \
              -I../Source/tmwxGUI/tmwxHtmlHelp -I../Source/tmwxGUI/tmwxInspector \
              -I../Source/tmwxGUI/tmwxLogFrame -I../Source/tmwxGUI/tmwxOptimizerDialog \
              -I../Source/tmwxGUI/tmwxPalette -I../Source/tmwxGUI/tmwxViewSettings \
              -I../Source/tmModel/wnlib/cmp -I../Source/tmModel/wnlib/conjdir \
              -I../Source/tmModel/wnlib/cpy -I../Source/tmModel/wnlib/list \
              -I../Source/tmModel/wnlib/low -I../Source/tmModel/wnlib/mat \
              -I../Source/tmModel/wnlib/mem -I../Source/tmModel/wnlib/random \
              -I../Source/tmModel/wnlib/vect"

# Find all source files, excluding test files
CPP_FILES=$(find ../Source -name "*.cpp" | grep -v "/test/")
C_FILES=$(find ../Source -name "*.c" | grep -v "/test/")

# Compiler flags
CXXFLAGS="-std=c++11 -O0 -g -DTMWX $WX_CXXFLAGS $INCLUDE_FLAGS"
CFLAGS="-O0 -g $INCLUDE_FLAGS"

# Add flags to suppress warnings in third-party code and set minimum macOS version
CXXFLAGS="$CXXFLAGS -Wno-deprecated-register -Wno-deprecated-declarations -Wno-int-to-void-pointer-cast -Wno-format -Wno-writable-strings -mmacosx-version-min=10.13"
CFLAGS="$CFLAGS -mmacosx-version-min=10.13"

# Clean up old object files and analysis results
rm -f *.o
rm -rf analysis-results

# Run static analysis
echo "Running Clang Static Analyzer..."
scan-build -o analysis-results \
  --use-analyzer=/usr/bin/clang \
  -enable-checker core \
  -enable-checker cplusplus \
  -enable-checker deadcode \
  -enable-checker security \
  -enable-checker unix \
  -v \
  clang++ $CXXFLAGS -c $CPP_FILES

# Also analyze C files
scan-build -o analysis-results \
  --use-analyzer=/usr/bin/clang \
  -enable-checker core \
  -enable-checker deadcode \
  -enable-checker security \
  -enable-checker unix \
  -v \
  clang $CFLAGS -c $C_FILES

echo "Static analysis complete! Check the analysis-results directory for the report."
