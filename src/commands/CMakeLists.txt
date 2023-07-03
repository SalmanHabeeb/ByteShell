# Create a library for the commands module
add_library(commands commands.c commands.h)

# Specify the include directories for the library
target_include_directories(commands PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(commands alias executor history llist lmap parse ulimit)