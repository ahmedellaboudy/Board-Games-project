cmake_minimum_required(VERSION 3.10)
project(BoardGames)

set(CMAKE_CXX_STANDARD 11)

add_executable(BoardGames
        MainMenu.cpp

        NumericalTicTacToe.cpp
        MisereTicTacToe.cpp
        XO_Classes.cpp
        XO_4x4_Classes.cpp
        XO_5X5_Classes.cpp
        sus.cpp
        obstacles_6x6_tictactoe.cpp
        infinity_XO.cpp
        Diamond_TicTacToe.cpp
        word.cpp
        Memory_TicTacToe.cpp
        pyramid_XO_Classes.cpp
        FourInARow.cpp
        ultimate_XO_Classes.cpp

        BoardGame_Classes.h
        NumericalTicTacToe.h
        MisereTicTacToe.h
        XO_Classes.h
        XO_4x4_Classes.h
        XO_5X5_Classes.h
        sus.h
        obstacles_6x6_tictactoe.h
        infinity_XO.h
        ValidatedUI.h
        Diamond_TicTacToe.h
        word.h
        Memory_TicTacToe.h
        pyramid_XO_Classes.h
        FourInARow.h
        ultimate_XO_Classes.h
        SUS_AI_Player.h
        FourInARow_AI_Player.h
)
