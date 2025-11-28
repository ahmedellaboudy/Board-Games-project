//@file XO_4x4_Classes.h
//@brief Defines the 4x4 Tic-Tac-Toe specific classes that extend the generic board game framework.
//
//This file provides:
//- `XO_4x4_Board`: A specialized board class for the 4x4 Tic-Tac-Toe game.
//- `XO_4x4_UI`: A user interface class tailored to 4x4 X-O game setup and player interaction.

#ifndef XO_4X4_CLASSES_H
#define XO_4X4_CLASSES_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
using namespace std;


// @class XO_4x4_Board
// @brief Represents the 4x4 Tic-Tac-Toe game board.
//
// This class inherits from the generic `Board<char>` class and implements
// the specific logic required for the 4x4 Tic-Tac-Toe game, including
// move updates, win/draw detection, and display functions.
//
// @see Board

class XO_4x4_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:

    /*  @brief Default constructor that initializes a 4x4 X-O board with starting positions.*/

    XO_4x4_Board();


    //  @brief Updates the board with a player's move.
    //  @param move Pointer to a Move<char> object containing move coordinates and symbol.
    //  @return true if the move is valid and successfully applied, false otherwise.

    bool update_board(Move<char>* move);


    
     // @brief Checks if the given player has won the game.
     // @param player Pointer to the player being checked.
     // @return true if the player has a winning line, false otherwise.


    bool is_win(Player<char>* player);


    //@brief Checks if the given player has lost the game.
    //@param player Pointer to the player being checked.
    //@return Always returns false (not used in X-O logic).

    bool is_lose(Player<char>*) { return false; };


    //@brief Checks if the game has ended in a draw.
    //@param player Pointer to the player being checked.
    //@return true if all cells are filled and no player has won, false otherwise.

    bool is_draw(Player<char>* player);


    //@brief Determines if the game is over (win or draw).
    //@param player Pointer to the player to evaluate.
    //@return true if the game has ended, false otherwise.

    bool game_is_over(Player<char>* player);


    // @brief Checks if a move to adjacent cell is valid.
    // @param from_x Original x position
    // @param from_y Original y position
    // @param to_x Target x position
    // @param to_y Target y position
    // @return true if the move is to an adjacent empty cell, false otherwise.

    bool is_valid_adjacent_move(int from_x, int from_y, int to_x, int to_y);


    //* @brief Gets all possible moves for a player.
    //* @param player Pointer to the player
    //* @return Vector of possible moves

    vector<Move<char>*> get_possible_moves(Player<char>* player);
};

//* @class XO_4x4_UI
//* @brief User Interface class for the 4x4 Tic-Tac-Toe game.
//*
//* Inherits from the generic `UI<char>` base class and provides
//* 4x4 X-O specific functionality for player setup and move input.
//*
//* @see UI

class XO_4x4_UI : public ValidatedUI<char> {
public:

    //* @brief Constructs an XO_4x4_UI object.
    //*
    //* Initializes the base `UI<char>` class with the welcome message for 4x4 X-O.

    XO_4x4_UI();


    /* * @brief Destructor for XO_4x4_UI.*/

    ~XO_4x4_UI() {};


    //* @brief Creates a player of the specified type.
    //* @param name Name of the player.
    //* @param symbol Character symbol ('X' or 'O') assigned to the player.
    //* @param type The type of the player (Human or Computer).
    //* @return Pointer to the newly created Player<char> instance.

    Player<char>* create_player(string& name, char symbol, PlayerType type);


    //* @brief Retrieves the next move from a player.
    //* @param player Pointer to the player whose move is being requested.
    //* @return A pointer to a new `Move<char>` object representing the player's action.

    virtual Move<char>* get_move(Player<char>* player);


    //* @brief Asks user for source and destination coordinates for moving tokens.
    //* @param player Pointer to the current player
    //* @return Pointer to Move object representing the move

    Move<char>* get_move_with_source(Player<char>* player);
};

#endif // XO_4X4_CLASSES_H