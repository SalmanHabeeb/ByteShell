# Create a library for the alias module
add_library(alias alias.c alias.h)

# Specify the include directories for the library
target_include_directories(alias PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(alias commands executor history llist lmap parse ulimit)