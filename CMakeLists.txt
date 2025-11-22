cmake_minimum_required(VERSION 3.16)
project(BoardGames)

set(CMAKE_CXX_STANDARD 17)

add_executable(BoardGamesApp
        MainMenu.cpp
        NumericalTicTacToe.cpp
)

add_executable(XO_Demo
        XO_Demo.cpp
        XO_Classes.cpp
)