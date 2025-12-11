/**
 * @file FourInARow.h
 * @brief Four-in-a-row game implementation (Game 2)
 * A 2D version of Connect Four where players mark a 6x7 grid.
 * Players must place marks in the lowest available square of any column.
 * Win condition: Four marks in a row (horizontally, vertically, or diagonally)
 */

#ifndef FOUR_IN_A_ROW_H
#define FOUR_IN_A_ROW_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <string>

using namespace std;

/**
 * @class FourInARow_Board
 * @brief Board class for Four-in-a-row game
 *
 * 6 rows x 7 columns grid where pieces "fall" to the bottom
 */
class FourInARow_Board : public Board<char> {
private:
    char blank_symbol = ' '; ///< Character for empty cell

    /**
     * @brief Find the lowest available row in a column
     * @param col The column to check
     * @return Row index of lowest empty cell, or -1 if column is full
     */
    int find_lowest_row(int col);

    /**
     * @brief Check if a player has four-in-a-row
     * @param symbol The symbol to check
     * @return true if four-in-a-row exists
     */
    bool check_four_in_row(char symbol);

    /**
     * @brief Check horizontal lines for four-in-a-row
     * @param symbol The symbol to check
     * @return true if found
     */
    bool check_horizontal(char symbol);

    /**
     * @brief Check vertical lines for four-in-a-row
     * @param symbol The symbol to check
     * @return true if found
     */
    bool check_vertical(char symbol);

    /**
     * @brief Check diagonal lines for four-in-a-row
     * @param symbol The symbol to check
     * @return true if found
     */
    bool check_diagonal(char symbol);

public:
    /**
     * @brief Constructor initializing 6x7 board
     */
    FourInARow_Board();

    /**
     * @brief Update board with a move (piece falls to bottom of column)
     * @param move The move containing column and symbol
     * @return true if move is valid, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has won (four-in-a-row)
     * @param player The player to check
     * @return true if player won
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has lost (not used in this game)
     * @param player The player to check
     * @return Always false
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game is a draw (board full, no winner)
     * @param player The player to check
     * @return true if board is full with no winner
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player The player to check
     * @return true if someone won or board is full
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class FourInARow_UI
 * @brief UI class for Four-in-a-row game
 */
class FourInARow_UI : public ValidatedUI<char> {
public:
    /**
     * @brief Constructor
     */
    FourInARow_UI();

    /**
     * @brief Destructor
     */
    ~FourInARow_UI() {}

    /**
     * @brief Create a player based on type (supports AI)
     * @param name Player name
     * @param symbol Player symbol ('X' or 'O')
     * @param type Player type (HUMAN or AI)
     * @return Pointer to created player
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Setup players with AI option
     * @return Array of two players
     */
    Player<char>** setup_players() override;

    /**
     * @brief Get move from player (human or AI)
     * For this game, players only choose a column (0-6)
     * @param player The player making the move
     * @return Move object with column choice
     */
    Move<char>* get_move(Player<char>* player) override;

protected:
    /**
     * @brief Override to add AI option
     */
    PlayerType get_player_type_choice(string player_label, const vector<string>& options) override;
};

#endif // FOUR_IN_A_ROW_H