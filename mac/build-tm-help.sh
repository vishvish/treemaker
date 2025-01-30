#!/bin/bash
# This script builds the help.zip file in build/TreeMaker.build/help/help.zip
# from the source code and puts it in the build directory, where it will be
# copied into the app the next time the XCode project TreeMaker.xcodeproj is built.

# Change to the script's directory
cd "$(dirname "$0")"

if [ ! -d build ]; then
  mkdir build
fi
if [ ! -d build/TreeMaker.build ]; then
  mkdir build/TreeMaker.build
fi
if [ ! -d build/TreeMaker.build/help ]; then
  mkdir build/TreeMaker.build/help
fi

# Go to the help source directory and create a zip file with all help content
cd ../Source/help
find . -type f \( -name '*.htm' -o -name '*.png' -o -name '*.hhp' -o -name '*.hhk' -o -name '*.hhc' -o -name '*.css' \) -print | zip -D ../../mac/build/TreeMaker.build/help/help.zip -@

# Create a simple cache file that maps the help file to its contents
echo "treemaker.hhp=help.zip" > ../../mac/build/TreeMaker.build/help/help.zip_zip_treemaker.hhp.cached

cd ../../mac
exit 0
