/**
 * @file NumericalTicTacToe_classes.h
 * @brief Numerical Tic-Tac-Toe game implementation (Game 9)
 * Player 1: Odd numbers (1, 3, 5, 7, 9)
 * Player 2: Even numbers (2, 4, 6, 8)
 * Win condition: Three numbers in a row that sum to 15
 */

#ifndef NUMERICAL_TICTACTOE_CLASSES_H
#define NUMERICAL_TICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
#include <set>
#include <algorithm>

/**
 * @class Numerical_Board
 * @brief Board class for Numerical Tic-Tac-Toe
 */
class Numerical_Board : public Board<int> {
private:
    std::set<int> used_numbers;
    int blank_value = 0;

public:
    /**
     * @brief Constructor initializing 3x3 board
     */
    Numerical_Board();

    /**
     * @brief Update board with a number move
     * @param move The move containing position and number
     * @return true if move is valid, false otherwise
     */
    bool update_board(Move<int>* move) override;

    /**
     * @brief Check if player has won (three numbers summing to 15)
     * @param player The player to check
     * @return true if player won, false otherwise
     */
    bool is_win(Player<int>* player) override;

    /**
     * @brief Check if player lost (not used in this game)
     * @param player The player to check
     * @return Always false
     */
    bool is_lose(Player<int>* player) override { return false; }

    /**
     * @brief Check if game is a draw
     * @param player The player to check
     * @return true if board is full with no winner
     */
    bool is_draw(Player<int>* player) override;

    /**
     * @brief Check if game is over
     * @param player The player to check
     * @return true if win or draw
     */
    bool game_is_over(Player<int>* player) override;

    /**
     * @brief Check if a number has been used
     * @param number The number to check
     * @return true if already used
     */
    bool is_number_used(int number) const;
};

/**
 * @class Numerical_Player
 * @brief Player class for Numerical Tic-Tac-Toe
 */
class Numerical_Player : public Player<int> {
private:
    std::set<int> available_numbers;  // Numbers this player can use

public:
    /**
     * @brief Constructor
     * @param name Player name
     * @param player_number Player number (1 for odd, 2 for even)
     */
    Numerical_Player(std::string name, int player_number);

    /**
     * @brief Get available numbers for this player
     * @return Set of available numbers
     */
    const std::set<int>& get_available_numbers() const { return available_numbers; }

    /**
     * @brief Remove a number from available set
     * @param number The number to remove
     */
    void use_number(int number);
};

/**
 * @class Numerical_Random_Player
 * @brief Computer player that makes random valid moves
 */
class Numerical_Random_Player : public Numerical_Player {
public:
    /**
     * @brief Constructor
     * @param player_number Player number (1 for odd, 2 for even)
     */
    Numerical_Random_Player(int player_number);
};

/**
 * @class Numerical_UI
 * @brief UI class for Numerical Tic-Tac-Toe
 */
class Numerical_UI : public UI<int> {
public:
    /**
     * @brief Constructor
     */
    Numerical_UI();

    /**
     * @brief Destructor
     */
    ~Numerical_UI() {}

    /**
     * @brief Get move from player (human or computer)
     * @param player The player making the move
     * @return Move object with position and number
     */
    Move<int>* get_move(Player<int>* player) override;

    /**
     * @brief Create a player based on type
     * @param name Player name
     * @param symbol Player number (1 or 2)
     * @param type Player type (HUMAN or COMPUTER)
     * @return Pointer to created player
     */
    Player<int>* create_player(std::string& name, int symbol, PlayerType type) override;

    /**
     * @brief Setup both players for the game
     * @return Array of two player pointers
     */
    Player<int>** setup_players() override;
};

#endif // NUMERICAL_TICTACTOE_CLASSES_H