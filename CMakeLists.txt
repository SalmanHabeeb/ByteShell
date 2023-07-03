# Set the minimum required version of cmake
cmake_minimum_required(VERSION 3.26.3)

# Set the project name and language
project(ByteShell C)

# Set the output directory for the executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Add the subdirectories that contain the source files
add_subdirectory(src/alias)
add_subdirectory(src/commands)
add_subdirectory(src/executor)
add_subdirectory(src/history)
add_subdirectory(src/llist)
add_subdirectory(src/lmap)
add_subdirectory(src/parse)
add_subdirectory(src/ulimit)

# Add the main executable and link it with the libraries
add_executable(main main.c)
target_link_libraries(main alias commands executor history llist lmap parse ulimit)
