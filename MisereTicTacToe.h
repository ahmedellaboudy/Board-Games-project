#ifndef MISERE_TICTACTOE_H
#define MISERE_TICTACTOE_H

#include <string>
#include <utility>

class MisereTicTacToe {
private:
    char board[3][3];
    char currentPlayer;
    std::string playerXName;
    std::string playerOName;
    bool isPlayerXHuman;
    bool isPlayerOHuman;

    void printBoard();
    bool threeInRow(char p);
    bool fullBoard();
    void resetBoard();
    void makeMove(int row, int col);
    std::pair<int,int> getComputerMove();

public:
    MisereTicTacToe();
    void setupPlayers();
    void play();
};

#endif
