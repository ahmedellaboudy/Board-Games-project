#ifndef DIAMOND_TICTACTOE_H
#define DIAMOND_TICTACTOE_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <string>
using namespace std;

class Diamond_board : public Board<char> {
private:
    /**
     * @brief Counts all three-in-a-row sequences for a given symbol (horizontal, vertical, and diagonals)
     * @param symbol The symbol to count sequences for (X or O)
     * @return Number of three-in-a-row sequences
     */
    char blank_symbol = ' ';
    bool count_four_in_row(char symbol);
    bool count_three_in_row(char symbol);

public:
    /**
     * @brief Constructor initializing 3x3 board
     */
    Diamond_board();

    void display() const;

    bool is_playable_cell(int row, int col) const {
        // Diamond shape pattern - symmetric
        switch(row) {
            case 0: return col == 3;
            case 1: return col >= 2 && col <= 4;
            case 2: return col >= 1 && col <= 5;
            case 3: return col >= 0 && col <= 6;
            case 4: return col >= 1 && col <= 5;
            case 5: return col >= 2 && col <= 4;
            case 6: return col == 3;
            default: return false;
        }
    }

    /**
     * @brief Update board with a move
     * @param move The move containing position and symbol
     * @return true if move is valid, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Check if player has WON
     * In Diamond, you win if your OPPONENT gets three-in-a-row
     * @param player The player to check
     * @return true if opponent has three-in-a-row
     */
    bool is_win(Player<char>* player) override;

    bool is_lose(Player<char> *player) override;

    /**
     * @brief Check if player has LOST
     * In Diamond, you lose if YOU get three-in-a-row
     * @param player The player to check
     * @return true if player has three-in-a-row
     */

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

class Diamond_UI : public ValidatedUI<char> {
public:
    /**
     * @brief Display the board in diamond shape
     */
    pair<int, int> display_to_matrix(int display_row, int display_col) const;

    void display_board_matrix(const vector<vector<char>> &matrix) const {
        cout << "\n";
        cout << "   0   1   2   3   4   5   6\n";
        cout << " -----------------------------\n";
        // Row 0: only column 3
        cout << "0            | " << (matrix[0][3] == ' ' ? ' ' : matrix[0][3]) << " |\n";
        cout << " -----------------------------\n";
        // Row 1: columns 2,3,4
        cout << "1        | " << (matrix[1][2] == ' ' ? ' ' : matrix[1][2]) << " | "
                             << (matrix[1][3] == ' ' ? ' ' : matrix[1][3]) << " | "
                             << (matrix[1][4] == ' ' ? ' ' : matrix[1][4]) << " |\n";
        cout << " -----------------------------\n";
        // Row 2: columns 1,2,3,4,5
        cout << "2    | " << (matrix[2][1] == ' ' ? ' ' : matrix[2][1]) << " | "
                         << (matrix[2][2] == ' ' ? ' ' : matrix[2][2]) << " | "
                         << (matrix[2][3] == ' ' ? ' ' : matrix[2][3]) << " | "
                         << (matrix[2][4] == ' ' ? ' ' : matrix[2][4]) << " | "
                         << (matrix[2][5] == ' ' ? ' ' : matrix[2][5]) << " |\n";
        cout << " -----------------------------\n";
        // Row 3: all 7 columns
        cout << "3| " << (matrix[3][0] == ' ' ? ' ' : matrix[3][0]) << " | "
                     << (matrix[3][1] == ' ' ? ' ' : matrix[3][1]) << " | "
                     << (matrix[3][2] == ' ' ? ' ' : matrix[3][2]) << " | "
                     << (matrix[3][3] == ' ' ? ' ' : matrix[3][3]) << " | "
                     << (matrix[3][4] == ' ' ? ' ' : matrix[3][4]) << " | "
                     << (matrix[3][5] == ' ' ? ' ' : matrix[3][5]) << " | "
                     << (matrix[3][6] == ' ' ? ' ' : matrix[3][6]) << " |\n";
        cout << " -----------------------------\n";
        // Row 4: columns 1,2,3,4,5
        cout << "4    | " << (matrix[4][1] == ' ' ? ' ' : matrix[4][1]) << " | "
                         << (matrix[4][2] == ' ' ? ' ' : matrix[4][2]) << " | "
                         << (matrix[4][3] == ' ' ? ' ' : matrix[4][3]) << " | "
                         << (matrix[4][4] == ' ' ? ' ' : matrix[4][4]) << " | "
                         << (matrix[4][5] == ' ' ? ' ' : matrix[4][5]) << " |\n";
        cout << " -----------------------------\n";
        // Row 5: columns 2,3,4
        cout << "5        | " << (matrix[5][2] == ' ' ? ' ' : matrix[5][2]) << " | "
                             << (matrix[5][3] == ' ' ? ' ' : matrix[5][3]) << " | "
                             << (matrix[5][4] == ' ' ? ' ' : matrix[5][4]) << " |\n";
        cout << " -----------------------------\n";
        // Row 6: only column 3
        cout << "6            | " << (matrix[6][3] == ' ' ? ' ' : matrix[6][3]) << " |\n";
        cout << " -----------------------------\n";
    }

    /**
     * @brief Constructor
     */
    Diamond_UI();

    ~Diamond_UI();

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
