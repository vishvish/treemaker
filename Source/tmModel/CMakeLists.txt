# Find all source files in the model directory and subdirectories
file(GLOB_RECURSE MODEL_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE MODEL_HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# Create the model library
add_library(tmmodel STATIC
    ${MODEL_SOURCES}
    ${MODEL_HEADERS}
)

target_include_directories(tmmodel PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/tmNLCO
    ${CMAKE_CURRENT_SOURCE_DIR}/tmSolvers
    ${CMAKE_CURRENT_SOURCE_DIR}/tmOptimizers
    ${CMAKE_CURRENT_SOURCE_DIR}/tmTreeClasses
    ${CMAKE_CURRENT_SOURCE_DIR}/tmPtrClasses
    ${CMAKE_CURRENT_SOURCE_DIR}/wnlib
    ${CMAKE_CURRENT_SOURCE_DIR}/wnlib/cmp
    ${CMAKE_CURRENT_SOURCE_DIR}/wnlib/conjdir
    ${CMAKE_CURRENT_SOURCE_DIR}/wnlib/cpy
    ${CMAKE_CURRENT_SOURCE_DIR}/wnlib/list
    ${CMAKE_CURRENT_SOURCE_DIR}/wnlib/low
    ${CMAKE_CURRENT_SOURCE_DIR}/wnlib/mat
    ${CMAKE_CURRENT_SOURCE_DIR}/wnlib/mem
    ${CMAKE_CURRENT_SOURCE_DIR}/wnlib/random
    ${CMAKE_CURRENT_SOURCE_DIR}/wnlib/vect
    ${CMAKE_SOURCE_DIR}/Source
)

# Add wxWidgets definitions since some model files might use wx types
target_compile_definitions(tmmodel PUBLIC TMWX)

target_link_libraries(tmmodel PUBLIC
    tmcore
    ${wxWidgets_LIBRARIES}
)
