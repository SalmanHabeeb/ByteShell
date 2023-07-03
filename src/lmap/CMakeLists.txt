# Create a library for the lmap module
add_library(lmap lmap.c lmap.h)

# Specify the include directories for the library
target_include_directories(lmap PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})