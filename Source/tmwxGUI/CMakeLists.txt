# Find all source files in the GUI directory and subdirectories
file(GLOB_RECURSE GUI_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE GUI_HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# Create the GUI library
add_library(tmwxgui STATIC
    ${GUI_SOURCES}
    ${GUI_HEADERS}
)

target_include_directories(tmwxgui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxCommon
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxDocView
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxFoldedForm
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxHtmlHelp
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxInspector
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxLogFrame
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxOptimizerDialog
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxPalette
    ${CMAKE_CURRENT_SOURCE_DIR}/tmwxViewSettings
    ${CMAKE_SOURCE_DIR}/Source
    ${CMAKE_SOURCE_DIR}/Source/tmModel
)

# Add wxWidgets definitions and includes
target_compile_definitions(tmwxgui PUBLIC TMWX)
target_include_directories(tmwxgui PUBLIC 
    ${wxWidgets_INCLUDE_DIRS}
)

target_link_libraries(tmwxgui PUBLIC
    tmcore
    tmmodel
    ${wxWidgets_LIBRARIES}
)
