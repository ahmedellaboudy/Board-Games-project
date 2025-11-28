#ifndef XO_6X6_CLASSES_H
#define XO_6X6_CLASSES_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// -----------------------------------------------------
// 6x6 Tic-Tac-Toe Board (4-in-a-row to win)
// -----------------------------------------------------
class XO_6x6_Board : public Board<char> {
private:
    const char blank_symbol = '.';
    int obstacles_count;

public:
    XO_6x6_Board();

    bool update_board(Move<char>* move);

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
    int get_obstacles_count();

    bool is_win(Player<char>* player);
    void display_scores(Player<char>* player1, Player<char>* player2);
    int get_moves_count() const { return n_moves; }
    int get_obstacles_count() const { return obstacles_count; }

    bool is_lose(Player<char>*) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    void add_random_obstacles();
};

// -----------------------------------------------------
// 6x6 Tic-Tac-Toe UI
// -----------------------------------------------------
class XO_6x6_UI : public ValidatedUI<char> {
public:
    XO_6x6_UI();
    ~XO_6x6_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};

class XO_6x6_GameManager {
private:
    XO_6x6_Board* board;
    Player<char>* players[2];
    XO_6x6_UI* ui;

public:
    XO_6x6_GameManager();
    ~XO_6x6_GameManager();
    void run();
};

#endif // XO_6X6_CLASSES_H