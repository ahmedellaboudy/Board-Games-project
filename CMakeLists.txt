cmake_minimum_required(VERSION 3.10)
project(BoardGames)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(BoardGames
        MainMenu.cpp
        NumericalTicTacToe.cpp
        MisereTicTacToe.cpp
        XO_Classes.cpp
        XO_4x4_Classes.cpp
        XO_5X5_Classes.cpp
        obstacles_6x6_tictactoe.cpp
)

# Optional: include header files for IDE navigation
target_include_directories(BoardGames PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
