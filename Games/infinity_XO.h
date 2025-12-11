// @file Infinity_XO_Classes.h
// @brief Defines the Infinity Tic-Tac-Toe game classes (Game 11).
// Rules: 3x3 grid where after every 3 moves, the oldest mark disappears.

#ifndef INFINITY_XO_CLASSES_H
#define INFINITY_XO_CLASSES_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <queue>
using namespace std;

/**
 * @class infinity_Board
 * @brief Represents the Infinity Tic-Tac-Toe game board.
 *
 * After every 3 moves, the oldest mark on the board disappears.
 * Win by aligning 3 marks before they vanish.
 */
class infinity_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character for empty cell
    queue<pair<int, int>> move_history; ///< Track move positions in order

public:
    /**
     * @brief Default constructor that initializes a 3x3 board.
     */
    infinity_Board();

    /**
     * @brief Updates the board with a player's move.
     * After every 3 moves, removes the oldest mark.
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Removes the oldest move from the board.
     */
    void remove_oldest_move();

    /**
     * @brief Checks if the given player has won the game.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the given player has lost the game.
     */
    bool is_lose(Player<char>*) override { return false; }

    /**
     * @brief Checks if the game has ended in a draw.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game is over (win or draw).
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class infinity_UI
 * @brief User Interface class for the Infinity Tic-Tac-Toe game.
 */
class infinity_UI : public ValidatedUI<char> {
public:
    /**
     * @brief Constructs an infinity_UI object.
     */
    infinity_UI();

    /**
     * @brief Destructor for infinity_UI.
     */
    ~infinity_UI() {}

    /**
     * @brief Creates a player of the specified type.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Retrieves the next move from a player.
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif // INFINITY_XO_CLASSES_H
