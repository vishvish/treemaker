cmake_minimum_required(VERSION 3.15)

# Set project name and version from tmVersion.h
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/Source/tmVersion.h" version_lines
    REGEX "^#define TM_VERSION_(MAJOR|MINOR|RELEASE)")
foreach(ver ${version_lines})
    if(ver MATCHES "^#define TM_VERSION_(MAJOR|MINOR|RELEASE) ([0-9]+)$")
        set(TM_VERSION_${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
    endif()
endforeach()

project(TreeMaker 
    VERSION ${TM_VERSION_MAJOR}.${TM_VERSION_MINOR}.${TM_VERSION_RELEASE}
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add compile definitions based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(TMDEBUG __WXDEBUG__)
elseif(CMAKE_BUILD_TYPE STREQUAL "Development")
    add_compile_definitions(TMDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Profile")
    add_compile_definitions(TMPROFILE)
endif()

# Find wxWidgets
set(wxWidgets_USE_STATIC 1)
set(wxWidgets_CONFIG_OPTIONS --toolkit=osx_cocoa --unicode)
find_package(wxWidgets 3.2 REQUIRED COMPONENTS core base adv html xml)
include(${wxWidgets_USE_FILE})

# Add subdirectories
add_subdirectory(Source)

# Installation rules
include(GNUInstallDirs)

# Install resources
install(DIRECTORY ${CMAKE_SOURCE_DIR}/help
        DESTINATION ${CMAKE_INSTALL_DATADIR}/TreeMaker
        FILES_MATCHING PATTERN "*.html" PATTERN "*.hhp" PATTERN "*.hhc")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/images
        DESTINATION ${CMAKE_INSTALL_DATADIR}/TreeMaker
        FILES_MATCHING PATTERN "*.png" PATTERN "*.jpg" PATTERN "*.xpm")

# macOS specific settings
if(APPLE)
    # Enable @rpath in the install name for any shared libraries
    set(CMAKE_MACOSX_RPATH 1)
    
    # Set deployment target
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment version")
    
    # Support both ARM and Intel
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "Build architectures for macOS")
endif()

# Package configuration
set(CPACK_PACKAGE_NAME "TreeMaker")
set(CPACK_PACKAGE_VENDOR "Robert J. Lang")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A Program for Origami Design")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "TreeMaker")

if(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_DMG_VOLUME_NAME "TreeMaker")
    set(CPACK_DMG_FORMAT "UDZO")
    
    # Set bundle properties
    set(MACOSX_BUNDLE_BUNDLE_NAME "TreeMaker")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.langorigami.treemaker")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}")
    set(MACOSX_BUNDLE_COPYRIGHT " 2003-2025 Robert J. Lang")
endif()

include(CPack)
