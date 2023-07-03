# Create a library for the history module
add_library(history history.c history.h)

# Specify the include directories for the library
target_include_directories(history PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(history alias commands executor llist lmap parse ulimit)