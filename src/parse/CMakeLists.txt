# Create a library for the parse module
add_library(parse parse.c parse.h)

# Specify the include directories for the library
target_include_directories(parse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(parse alias commands executor history llist lmap ulimit)