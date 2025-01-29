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
CXXFLAGS="-std=c++11 -O2 -DTMWX $WX_CXXFLAGS $INCLUDE_FLAGS"
CFLAGS="-O2 $INCLUDE_FLAGS"

# Add flags to suppress warnings in third-party code and set minimum macOS version
CXXFLAGS="$CXXFLAGS -Wno-deprecated-register -Wno-deprecated-declarations -Wno-int-to-void-pointer-cast -Wno-format -Wno-writable-strings -mmacosx-version-min=10.13"
CFLAGS="$CFLAGS -mmacosx-version-min=10.13"

# Clean up old object files
rm -f *.o

# Compile
echo "Compiling TreeMaker..."
# Compile C++ files
clang++ $CXXFLAGS -c $CPP_FILES
# Compile C files
clang $CFLAGS -c $C_FILES

# Link
echo "Linking TreeMaker..."
clang++ *.o $WX_LIBS -o build/Release/TreeMaker.app/Contents/MacOS/TreeMaker

# Copy resources
echo "Copying resources..."
cp resources/Icon_app.icns build/Release/TreeMaker.app/Contents/Resources/
cp resources/Icon_doc.icns build/Release/TreeMaker.app/Contents/Resources/
cp build/TreeMaker.build/help/help.zip build/Release/TreeMaker.app/Contents/SharedSupport/
cp build/TreeMaker.build/help/help.zip_zip_treemaker.hhp.cached build/Release/TreeMaker.app/Contents/SharedSupport/
cp ../Source/images/SplashScreen.png build/Release/TreeMaker.app/Contents/SharedSupport/
cp ../Source/about/about.htm build/Release/TreeMaker.app/Contents/SharedSupport/

# Create Info.plist
cat > build/Release/TreeMaker.app/Contents/Info.plist << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleDevelopmentRegion</key>
    <string>English</string>
    <key>CFBundleExecutable</key>
    <string>TreeMaker</string>
    <key>CFBundleIconFile</key>
    <string>Icon_app</string>
    <key>CFBundleIdentifier</key>
    <string>com.langorigami.TreeMaker</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>TreeMaker</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleShortVersionString</key>
    <string>5.0</string>
    <key>CFBundleSignature</key>
    <string>????</string>
    <key>CFBundleVersion</key>
    <string>5.0</string>
    <key>LSMinimumSystemVersion</key>
    <string>10.13</string>
    <key>NSHighResolutionCapable</key>
    <true/>
</dict>
</plist>
EOF

echo "Build complete!"
