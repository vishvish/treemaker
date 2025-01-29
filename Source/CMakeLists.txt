# Add model library first since GUI depends on it
add_subdirectory(tmModel)

# Add GUI library
add_subdirectory(tmwxGUI)

# Core library
add_library(tmcore STATIC
    tmHeader.cpp
    tmPrec.cpp
)

target_include_directories(tmcore PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxGUI/tmwxCommon
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxGUI/tmwxLogFrame
    ${CMAKE_CURRENT_SOURCE_DIR}/tmModel
)

# Add compile definitions
target_compile_definitions(tmcore PUBLIC TMWX)

target_link_libraries(tmcore PUBLIC
    tmmodel
    ${wxWidgets_LIBRARIES}
)

# Optional: Add test directory
option(BUILD_TESTING "Build the testing tree." OFF)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

# Main executable
add_executable(TreeMaker MACOSX_BUNDLE)

target_sources(TreeMaker PRIVATE
    tmHeader.cpp
)

target_link_libraries(TreeMaker PRIVATE
    tmcore
    tmmodel
    tmwxgui
    ${wxWidgets_LIBRARIES}
)

# Set macOS bundle properties
if(APPLE)
    set_target_properties(TreeMaker PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.langorigami.treemaker"
        MACOSX_BUNDLE_BUNDLE_NAME "TreeMaker"
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
        RESOURCE "${CMAKE_SOURCE_DIR}/mac/resources/TreeMaker.icns"
    )
endif()

# Install rules
install(TARGETS TreeMaker
    BUNDLE DESTINATION . COMPONENT Runtime
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
)
