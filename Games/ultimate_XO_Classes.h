/**
* @file ultimate_XO_Classes.h
 * @brief Ultimate Tic Tac Toe game classes
 */

#ifndef ULTIMATE_TIC_TAC_TOE_CLASSES_H
#define ULTIMATE_TIC_TAC_TOE_CLASSES_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include "XO_Classes.h"
#include <vector>
#include <iostream>

using namespace std;

/**
 * @class Ultimate_XO_Board
 * @brief 3x3 grid where each cell contains a 3x3 Tic-Tac-Toe board
 */
class Ultimate_XO_Board : public Board<char> {
private:
    vector<vector<X_O_Board*>> subBoards;  // 3x3 grid of sub-boards
    vector<vector<char>> mainBoard;        // Track winners of each sub-board

public:
    Ultimate_XO_Board();
    ~Ultimate_XO_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override { return false; }
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    // Helper methods
    char check_sub_board_winner(int boardRow, int boardCol);
    bool is_board_available(int boardRow, int boardCol);
    X_O_Board* get_sub_board(int row, int col) const;
    vector<vector<char>> get_main_board() const { return mainBoard; }
};

/**
 * @class Ultimate_XO_UI
 * @brief User Interface for Ultimate Tic Tac Toe
 */
class Ultimate_XO_UI : public ValidatedUI<char> {
public:
    Ultimate_XO_UI();
    ~Ultimate_XO_UI() {}

    Move<char>* get_move(Player<char>* player) override;
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    // Display helpers
    void display_full_board(Ultimate_XO_Board* board) const;
    void display_main_board(Ultimate_XO_Board* board) const;
};

#endif // ULTIMATE_TIC_TAC_TOE_CLASSES_H
