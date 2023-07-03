# Create a library for the ulimit module
add_library(ulimit ulimit.c ulimit.h)

# Specify the include directories for the library
target_include_directories(ulimit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ulimit alias commands executor history llist lmap parse)