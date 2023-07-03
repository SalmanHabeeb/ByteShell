# Create a library for the llist module
add_library(llist llist.c llist.h)

# Specify the include directories for the library
target_include_directories(llist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(llist alias commands executor history lmap parse ulimit)