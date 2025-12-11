/**
 * @file obstacles_6x6_tictactoe.h
 * @brief Defines the 6x6 Tic-Tac-Toe with Obstacles game specific classes.
 *
 * This file provides:
 * - `XO_6x6_Board`: A specialized board class for the 6x6 Tic-Tac-Toe game with dynamic obstacles.
 * - `XO_6x6_UI`: A user interface class tailored to 6x6 X-O game with obstacles.
 * - `XO_6x6_GameManager`: A game manager class to coordinate the game flow.
 */

#ifndef XO_6X6_CLASSES_H
#define XO_6X6_CLASSES_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/**
 * @class XO_6x6_Board
 * @brief Represents the 6x6 Tic-Tac-Toe game board with obstacles.
 *
 * This class implements a 6x6 board where players try to connect 4 symbols
 * in a row (horizontally, vertically, or diagonally). Random obstacles are
 * added after every two moves to increase difficulty.
 */
class XO_6x6_Board : public Board<char> {
private:
    const char blank_symbol = '.'; ///< Character used to represent an empty cell
    int obstacles_count; ///< Counter for the number of obstacles placed on the board

public:
    /**
     * @brief Default constructor that initializes a 6x6 board.
     *
     * Initializes the board with empty cells and no obstacles at the start.
     */
    XO_6x6_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if four symbols are connected in a row.
     * @param sym The symbol to check for ('X' or 'O').
     * @return true if four symbols are connected in any direction, false otherwise.
     */
    bool check_four_in_row(char sym) {
        const int N = 6;

        // Check Horizontal
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= N - 4; j++) {
                if (board[i][j] == sym &&
                    board[i][j + 1] == sym &&
                    board[i][j + 2] == sym &&
                    board[i][j + 3] == sym)
                    return true;
            }
        }

        // Check Vertical
        for (int i = 0; i <= N - 4; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == sym &&
                    board[i + 1][j] == sym &&
                    board[i + 2][j] == sym &&
                    board[i + 3][j] == sym)
                    return true;
            }
        }

        // Check Main Diagonal
        for (int i = 0; i <= N - 4; i++) {
            for (int j = 0; j <= N - 4; j++) {
                if (board[i][j] == sym &&
                    board[i + 1][j + 1] == sym &&
                    board[i + 2][j + 2] == sym &&
                    board[i + 3][j + 3] == sym)
                    return true;
            }
        }

        // Check Anti-Diagonal
        for (int i = 0; i <= N - 4; i++) {
            for (int j = 3; j < N; j++) {
                if (board[i][j] == sym &&
                    board[i + 1][j - 1] == sym &&
                    board[i + 2][j - 2] == sym &&
                    board[i + 3][j - 3] == sym)
                    return true;
            }
        }

        return false;
    }

    /**
     * @brief Get the number of obstacles currently on the board.
     * @return The count of obstacles.
     */
    int get_obstacles_count();

    /**
     * @brief Checks if the given player has won the game.
     * @param player Pointer to the player being checked.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Display the scores of both players.
     * @param player1 Pointer to the first player.
     * @param player2 Pointer to the second player.
     */
    void display_scores(Player<char>* player1, Player<char>* player2);

    /**
     * @brief Get the current number of moves made.
     * @return The number of moves.
     */
    int get_moves_count() const { return n_moves; }

    /**
     * @brief Get the current number of obstacles.
     * @return The number of obstacles.
     */
    int get_obstacles_count() const { return obstacles_count; }

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false (not used in this game).
     */
    bool is_lose(Player<char>*) { return false; }

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if the board is full and no player has won, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (win or draw).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Adds random obstacles to the board.
     *
     * Places 2 random obstacles ('#') on empty cells.
     */
    void add_random_obstacles();
};

/**
 * @class XO_6x6_UI
 * @brief User Interface class for the 6x6 Tic-Tac-Toe with Obstacles game.
 *
 * Inherits from ValidatedUI and provides game-specific functionality
 * for player setup and move input.
 */
class XO_6x6_UI : public ValidatedUI<char> {
public:
    /**
     * @brief Constructs an XO_6x6_UI object.
     *
     * Initializes the UI with a welcome message and game rules.
     */
    XO_6x6_UI();

    /**
     * @brief Destructor for XO_6x6_UI.
     */
    ~XO_6x6_UI();

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('X' or 'O') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new Move<char> object representing the player's action.
     */
    virtual Move<char>* get_move(Player<char>* player);
};

/**
 * @class XO_6x6_GameManager
 * @brief Game Manager class for the 6x6 Tic-Tac-Toe with Obstacles game.
 *
 * Manages the game flow, including board initialization, player setup,
 * and the main game loop.
 */
class XO_6x6_GameManager {
private:
    XO_6x6_Board* board; ///< Pointer to the game board
    Player<char>* players[2]; ///< Array of two players
    XO_6x6_UI* ui; ///< Pointer to the user interface

public:
    /**
     * @brief Default constructor that initializes the game components.
     */
    XO_6x6_GameManager();

    /**
     * @brief Destructor that cleans up allocated memory.
     */
    ~XO_6x6_GameManager();

    /**
     * @brief Runs the game loop until completion.
     */
    void run();
};

#endif // XO_6X6_CLASSES_H
