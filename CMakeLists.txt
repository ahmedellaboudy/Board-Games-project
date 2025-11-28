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
        sus.h
        sus.cpp
        obstacles_6x6_tictactoe.cpp
        obstacles_6x6_tictactoe.h
        infinity_XO.cpp
        infinity_XO.h
        ValidatedUI.h
)

add_executable(XO_Classes.h
        XO_Classes.cpp
        BoardGame_Classes.h
)