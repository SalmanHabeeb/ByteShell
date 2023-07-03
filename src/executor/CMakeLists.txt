# Create a library for the executor module
add_library(executor executor.c executor.h)

# Specify the include directories for the library
target_include_directories(executor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(executor alias commands history llist lmap parse ulimit)