cmake_minimum_required(VERSION 3.10)

project(BoardGame LANGUAGES CXX)

# Use C++17 (you can change this if needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
        main_menu.cpp
        SUS_classes.cpp
        XO_Classes.cpp
        misere_classes.cpp
        misere_classes.h
)

# Create the executable
add_executable(BoardGame ${SOURCES})

# Include current directory so .h files are found
target_include_directories(BoardGame PRIVATE ${CMAKE_SOURCE_DIR})