cmake_minimum_required(VERSION 3.15)

set(TM_VERSION_MAJOR 5)
set(TM_VERSION_MINOR 1)
set(TM_VERSION_RELEASE 2)

# Set project name and version from tmVersion.h
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/Source/tmVersion.h" version_lines
    REGEX "^#define TM_VERSION_(MAJOR|MINOR|RELEASE)")
foreach(ver ${version_lines})
    if(ver MATCHES "^#define TM_VERSION_(MAJOR|MINOR|RELEASE) ([0-9]+)$")
        set(TM_VERSION_${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
    endif()
endforeach()

project(TreeMaker VERSION ${TM_VERSION_MAJOR}.${TM_VERSION_MINOR}.${TM_VERSION_RELEASE} LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add clang-specific flags for C++20
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
endif()

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
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DNDEBUG -DWX_SUPPRESS_SIZER_FLAGS_CHECK)
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

    # paths for the resources
    set(BUILD_HELP "${CMAKE_SOURCE_DIR}/mac/build-tm-help.sh")
    set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/mac/resources")
    set(SHARED_SUPPORT_DIR "${CMAKE_BINARY_DIR}/bin/TreeMaker.app/Contents/SharedSupport")
    set(RESOURCES_DIR "${CMAKE_BINARY_DIR}/bin/TreeMaker.app/Contents/Resources")
    set(HELP_DIR "${CMAKE_SOURCE_DIR}/mac/build/TreeMaker.build/help")

    # Build help
    add_custom_command(
       OUTPUT ${HELP_DIR}/help.zip
       COMMAND ${CMAKE_COMMAND} -E echo "Building help..."
       COMMAND ${BUILD_HELP}
       COMMENT "Building help..."
    )
    add_custom_target(help_files ALL
       DEPENDS ${HELP_DIR}/help.zip
    )

    # Copy resources
    add_custom_command(
       OUTPUT ${RESOURCES_DIR}/Icon_app.icns ${RESOURCES_DIR}/Icon_doc.icns ${HELP_DIR}/help.zip
       COMMAND ${CMAKE_COMMAND} -E echo "Copying resources..."
       COMMAND ${CMAKE_COMMAND} -E make_directory ${RESOURCES_DIR}
       COMMAND ${CMAKE_COMMAND} -E make_directory ${SHARED_SUPPORT_DIR}
       COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCE_DIR}/Icon_app.icns ${RESOURCES_DIR}/Icon_app.icns
       COMMAND ${CMAKE_COMMAND} -E copy ${RESOURCE_DIR}/Icon_doc.icns ${RESOURCES_DIR}/Icon_doc.icns
       COMMAND ${CMAKE_COMMAND} -E copy ${HELP_DIR}/help.zip ${SHARED_SUPPORT_DIR}/help.zip
       COMMAND ${CMAKE_COMMAND} -E copy ${HELP_DIR}/help.zip_zip_treemaker.hhp.cached ${SHARED_SUPPORT_DIR}/help.zip_zip_treemaker.hhp.cached
       COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Source/images/SplashScreen.png ${SHARED_SUPPORT_DIR}/SplashScreen.png
       COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/Source/about/about.htm ${SHARED_SUPPORT_DIR}/about.htm
       DEPENDS ${RESOURCE_DIR}/Icon_app.icns ${RESOURCE_DIR}/Icon_doc.icns
    )

    add_custom_target(copy_resources ALL
       DEPENDS ${RESOURCES_DIR}/Icon_app.icns ${RESOURCES_DIR}/Icon_doc.icns
    )

    add_dependencies(copy_resources help_files)
    add_dependencies(TreeMaker copy_resources)

 endif()

include(CPack)
