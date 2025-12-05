/**
 * @file MisereTicTacToe.h

 * Also known as Inverse Tic-Tac-Toe - the goal is to AVOID getting three-in-a-row!
 * A player LOSES if they complete a line of three marks.
 */

#ifndef MEMORY_TICTACTOE_H
#define MEMORY_TICTACTOE_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <string>

using namespace std;

/**
 * @class Memory_Board

 *
 * In this variant, getting three-in-a-row means you LOSE!
 */
class Fake_Board : public Board<char> {

    char blank_symbol = ' ';
public:

    bool update_board(Move<char>* move) override { return true; } // dummy
    bool is_win(Player<char>*) override { return false; }
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>*) override { return false; }
    bool game_is_over(Player<char>*) override { return false; }
    Fake_Board();
    void display_board() ;
};
class Memory_Board : public Board<char> {
private:
    char blank_symbol = ' '; ///< Character for empty cell

    /**
     * @brief Helper function to check if a player has three-in-a-row
     * @param symbol The symbol to check
     * @return true if three-in-a-row exists (which means LOSS in Misere)
     */
    bool has_three_in_row(char symbol);

public:
    /**
     * @brief Constructor initializing 3x3 board
     */
    Memory_Board();
    void display_board() ;

    /**
     * @brief Update board with a move
     * @param move The move containing position and symbol
     * @return true if move is valid, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has WON
     * In Memory, you win if your OPPONENT gets three-in-a-row
     * @param player The player to check
     * @return true if opponent has three-in-a-row
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Check if player has LOST
     * @param player The player to check
     * @return true if player has three-in-a-row
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Check if game is a draw
     * Draw occurs when board is full and nobody got three-in-a-row
     * @param player The player to check
     * @return true if board is full with no three-in-a-row
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Check if game is over
     * @param player The player to check
     * @return true if someone got three-in-a-row or board is full
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class Memory_UI
 * @brief UI class for Misere Tic-Tac-Toe
 */
class Memory_UI : public ValidatedUI<char> {
public:
    /**
     * @brief Constructor
     */
    Memory_UI();

    /**
     * @brief Destructor
     */
    ~Memory_UI() {}

    /**
     * @brief Create a player based on type
     * @param name Player name
     * @param symbol Player symbol ('X' or 'O')
     * @param type Player type (HUMAN or COMPUTER)
     * @return Pointer to created player
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Get move from player (human or computer)
     * @param player The player making the move
     * @return Move object with position and symbol
     */
    Move<char>* get_move(Player<char>* player) override;
};

#endif