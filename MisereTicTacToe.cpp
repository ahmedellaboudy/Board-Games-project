#include "MisereTicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <tuple>
using std::tie;   // optional



using namespace std;

MisereTicTacToe::MisereTicTacToe() {
    srand(static_cast<unsigned int>(time(0)));
    resetBoard();
    currentPlayer = 'X';
}

void MisereTicTacToe::resetBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void MisereTicTacToe::printBoard() {
    cout << "\n   0   1   2\n";
    for (int i = 0; i < 3; i++) {
        cout << i << "  " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
        if (i != 2) cout << "  ---+---+---\n";
    }
    cout << "\n";
}

bool MisereTicTacToe::threeInRow(char p) {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p) return true;

    for (int i = 0; i < 3; i++)
        if (board[0][i] == p && board[1][i] == p && board[2][i] == p) return true;

    if (board[0][0] == p && board[1][1] == p && board[2][2] == p) return true;
    if (board[0][2] == p && board[1][1] == p && board[2][0] == p) return true;

    return false;
}

bool MisereTicTacToe::fullBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return false;
    return true;
}

void MisereTicTacToe::setupPlayers() {
    int choice;

    // Player X
    cout << "Enter name for Player 1 (X): ";
    getline(cin, playerXName);
    do {
        cout << "Choose Player 1 type:\n1. Human\n2. Computer\n ";
        cin >> choice;
        cin.ignore();
        if (choice == 1) isPlayerXHuman = true;
        else if (choice == 2) isPlayerXHuman = false;
        else cout << "Invalid choice! Try again.\n";
    } while (choice != 1 && choice != 2);

    // Player O
    cout << "Enter name for Player 2 (O): ";
    getline(cin, playerOName);
    do {
        cout << "Choose Player 2 type:\n1. Human\n2. Computer\n ";
        cin >> choice;
        cin.ignore();
        if (choice == 1) isPlayerOHuman = true;
        else if (choice == 2) isPlayerOHuman = false;
        else cout << "Invalid choice! Try again.\n";
    } while (choice != 1 && choice != 2);
}

void MisereTicTacToe::makeMove(int row, int col) {
    board[row][col] = currentPlayer;
}

pair<int,int> MisereTicTacToe::getComputerMove() {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');
    return {row, col};
}

void MisereTicTacToe::play() {
    setupPlayers();
    resetBoard();
    currentPlayer = 'X';

    while (true) {
        printBoard();
        int row, col;
        string currentName = (currentPlayer == 'X') ? playerXName : playerOName;
        bool isHuman = (currentPlayer == 'X') ? isPlayerXHuman : isPlayerOHuman;

        if (isHuman) {
            cout << currentName << " (" << currentPlayer << "), enter row and column (0-2): ";
            while (!(cin >> row >> col) || row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid move! Try again: ";
            }
            cin.ignore();
        } else {
            cout << currentName << " (" << currentPlayer << ") is making a move...\n";
            tie(row, col) = getComputerMove();
        }

        makeMove(row, col);

        if (threeInRow(currentPlayer)) {
            printBoard();
            cout << currentName << " made 3-in-a-row and LOSES!\n";
            return;
        }

        if (fullBoard()) {
            printBoard();
            cout << "Draw! No 3-in-a-row.\n";
            return;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}
