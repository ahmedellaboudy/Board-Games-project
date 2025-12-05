/**
 * @file Ultimate_Tic_Tac_Toe_Classes.h
 * @brief Defines the Ultimate Tic Tac Toe game classes.
 *
 * This file provides:
 * - `Ultimate_Tic_Tac_Toe_Board`: A 3x3 board where each cell contains a 3x3 sub-board.
 * - `Ultimate_Tic_Tac_Toe_UI`: User interface for Ultimate Tic Tac Toe.
 */

#ifndef ULTIMATE_TIC_TAC_TOE_CLASSES_H
#define ULTIMATE_TIC_TAC_TOE_CLASSES_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <vector>
#include <memory>

using namespace std;

/**
 * @class Ultimate_Tic_Tac_Toe_Board
 * @brief Represents the Ultimate Tic Tac Toe game board.
 *
 * Consists of a 3x3 main board where each cell contains a 3x3 X-O board.
 */
class Ultimate_XO_Board : public Board<char> {
private:
    vector<vector<X_O_Board*>> subBoards;  ///< 3x3 grid of X_O_Board pointers
    vector<vector<char>> mainBoard;        ///< 3x3 main board (winners of sub-boards)
    int lastMoveBoardRow;                  ///< Row of the last move's board
    int lastMoveBoardCol;                  ///< Column of the last move's board
    char blank_symbol = '.';              ///< Empty cell symbol
    char tie_symbol = 'T';                ///< Tie symbol for sub-board

public:
    /**
     * @brief Constructor initializes all sub-boards.
     */
    Ultimate_XO_Board();

    /**
     * @brief Destructor cleans up sub-boards.
     */
    ~Ultimate_XO_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object.
     * @return true if move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if a specific sub-board is won.
     * @param row Row index of sub-board.
     * @param col Column index of sub-board.
     * @return Character of winner, tie_symbol for tie, or blank_symbol for ongoing.
     */
    char check_sub_board_win(int row, int col);

    /**
     * @brief Checks if the given player has won the main board.
     * @param player Pointer to the player being checked.
     * @return true if player has won the main board.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost (not used in this game).
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game is a draw.
     * @param player Pointer to the player (for interface consistency).
     * @return true if all sub-boards are completed with no main winner.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over.
     * @param player Pointer to the player.
     * @return true if game has ended (win or draw).
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Gets the available boards for the next move.
     * @return Vector of pairs (row,col) of available boards.
     */
    vector<pair<int, int>> get_available_boards();

    /**
     * @brief Displays the entire Ultimate Tic Tac Toe board.
     */
    void display_board() const;
};

/**
 * @class Ultimate_Tic_Tac_Toe_UI
 * @brief User Interface for Ultimate Tic Tac Toe game.
 */
class Ultimate_XO_UI : public ValidatedUI<char> {
public:
    /**
     * @brief Constructor with welcome message.
     */
    Ultimate_XO_UI();

    /**
     * @brief Destructor.
     */
    ~Ultimate_XO_UI() {};

    /**
     * @brief Creates a player of specified type.
     * @param name Player name.
     * @param symbol Player symbol ('X' or 'O').
     * @param type Player type (Human or Computer).
     * @return Pointer to new Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Gets the next move from a player.
     * @param player Pointer to the player.
     * @return Pointer to new Move<char> object.
     */
    virtual Move<char>* get_move(Player<char>* player);
};

#endif // ULTIMATE_TIC_TAC_TOE_CLASSES_H
