cmake_minimum_required(VERSION 3.10)
project(BoardGames)

set(CMAKE_CXX_STANDARD 11)

add_executable(BoardGames
        MainMenu.cpp
        BoardGame_Classes.h
        NumericalTicTacToe.cpp
        NumericalTicTacToe.h
        MisereTicTacToe.cpp
        MisereTicTacToe.h
        XO_Classes.cpp
        XO_Classes.h
        XO_4x4_Classes.cpp
        XO_4x4_Classes.h
        XO_5X5_Classes.cpp
        XO_5X5_Classes.h
)

add_executable(XO_Demo
        XO_Demo.cpp
        BoardGame_Classes.h
)