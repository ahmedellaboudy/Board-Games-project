/**
 * @file Pyramid_XO_Classes.h
 * @brief Defines the Pyramid X-O (Pyramid Tic-Tac-Toe) specific classes.
 *
 * This file provides:
 * - `Pyramid_Board`: A specialized board class for the Pyramid Tic-Tac-Toe game.
 * - `Pyramid_UI`: A user interface class tailored to Pyramid X-O game.
 */

#ifndef PYRAMID_XO_CLASSES_H
#define PYRAMID_XO_CLASSES_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
using namespace std;

/**
 * @class Pyramid_Board
 * @brief Represents the Pyramid Tic-Tac-Toe game board.
 *
 * The board has a pyramid shape with 9 cells arranged in 4 rows:
 * - Row 0: 1 cell (top)
 * - Row 1: 2 cells
 * - Row 2: 3 cells
 * - Row 3: 3 cells (base)
 * Total: 9 cells
 */
class Pyramid_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell
    vector<vector<bool>> valid_cells; ///< Matrix indicating valid pyramid positions

public:
    /**
     * @brief Default constructor that initializes a pyramid-shaped board.
     */
    Pyramid_Board();

    /**
     * @brief Updates the board with a player's move.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won the game.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game.
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game has ended in a draw.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Checks if a cell position is valid in the pyramid.
     */
    bool is_valid_cell(int x, int y) const;

    /**
     * @brief Display the pyramid board in proper shape.
     */
};

/**
 * @class Pyramid_UI
 * @brief User Interface class for the Pyramid X-O game.
 */
class Pyramid_UI : public ValidatedUI<char> {
public:
    /**
     * @brief Constructs a Pyramid_UI object.
     */
    Pyramid_UI();

    /**
     * @brief Destructor for Pyramid_UI.
     */
    ~Pyramid_UI() {};

    /**
     * @brief Creates a player of the specified type.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Display the pyramid board with proper formatting.
     */
    virtual void display_board_matrix(const vector<vector<char>>& matrix) const;
};

#endif // PYRAMID_XO_CLASSES_H
