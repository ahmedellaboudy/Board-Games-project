#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include "Pyramid_XO_Classes.h"

using namespace std;

Pyramid_Board::Pyramid_Board() : Board(3, 5) {

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (i == 0 && j == 2) { 
                board[i][j] = blank_symbol;
            }
            else if (i == 1 && j >= 1 && j <= 3) {
                board[i][j] = blank_symbol;
            }
            else if (i == 2 && j >= 0 && j <= 4) {
                board[i][j] = blank_symbol;
            }
            else {
                board[i][j] = ' ';
            }
        }
    }
}

bool Pyramid_Board::is_valid_cell(int x, int y) const {
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }

    if (x == 0 && y == 2) {
        return true;
    }
    else if (x == 1 && y >= 1 && y <= 3) {
        return true;
    }
    else if (x == 2 && y >= 0 && y <= 4) {
        return true;
    }

    return false;
}

bool Pyramid_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (is_valid_cell(x, y) && board[x][y] == blank_symbol) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    return false;
}

bool Pyramid_Board::is_win(Player<char>* player) {
    const char sym = toupper(player->get_symbol());

    if (board[1][1] == sym && board[1][2] == sym && board[1][3] == sym) return true;

    if (board[2][0] == sym && board[2][1] == sym && board[2][2] == sym) return true;
    if (board[2][1] == sym && board[2][2] == sym && board[2][3] == sym) return true;
    if (board[2][2] == sym && board[2][3] == sym && board[2][4] == sym) return true;

    if (board[0][2] == sym && board[1][2] == sym && board[2][2] == sym) return true;

    if (board[1][1] == sym && board[2][1] == sym) {
        if (board[0][2] == sym) return true;
    }
    if (board[1][3] == sym && board[2][3] == sym) {
        if (board[0][2] == sym) return true;
    }

    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) return true;

    if (board[0][2] == sym && board[1][3] == sym && board[2][4] == sym) return true;

    if (board[1][1] == sym && board[2][2] == sym && board[0][2] == sym) return true;

    if (board[1][3] == sym && board[2][2] == sym && board[0][2] == sym) return true;

    if (board[2][0] == sym && board[2][2] == sym && board[2][4] == sym) return true;
    if (board[2][0] == sym && board[1][2] == sym && board[2][4] == sym) return true;

    if (board[1][2] == sym && board[2][1] == sym && board[2][3] == sym) return true;
    if (board[0][2] == sym && board[2][1] == sym && board[2][3] == sym) return true;

    return false;
}

bool Pyramid_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Pyramid_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

Pyramid_UI::Pyramid_UI() : ValidatedUI<char>("Welcome to Pyramid X-O Game (3 Rows)", 3) {}

Player<char>* Pyramid_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Pyramid_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol() << ") ";
        cout << "enter your move (row 0-2 and column 0-4): ";
        cin >> x >> y;

        while (cin.fail() || !dynamic_cast<Pyramid_Board*>(player->get_board_ptr())->is_valid_cell(x, y)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid position! Valid positions are:\n";
            cout << "\nEnter valid row and column: ";
            cin >> x >> y;
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        Pyramid_Board* board = dynamic_cast<Pyramid_Board*>(player->get_board_ptr());

        do {
            int pos = rand() % 9;
            switch (pos) {
            case 0: x = 0; y = 2; break;
            case 1: x = 1; y = 1; break;
            case 2: x = 1; y = 2; break;
            case 3: x = 1; y = 3; break;
            case 4: x = 2; y = 0; break;
            case 5: x = 2; y = 1; break;
            case 6: x = 2; y = 2; break;
            case 7: x = 2; y = 3; break;
            case 8: x = 2; y = 4; break; 
            }
        } while (board->get_cell(x, y) != '.');

        cout << "\nComputer chooses position (" << x << ", " << y << ")\n";
    }
    return new Move<char>(x, y, player->get_symbol());
}

void Pyramid_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    if (matrix.empty() || matrix[0].empty()) return;

    cout << "\nPyramid Tic-Tac-Toe Board (3 Rows):\n\n";

    cout << "    ";
    for (int j = 0; j < 5; ++j) {
        cout << setw(3) << j;
    }
    cout << "\n";
    cout << "   " << string(18, '-') << "\n";

    for (int i = 0; i < 3; ++i) {
        cout << setw(2) << i << " |";
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] != ' ') {
                cout << setw(3) << matrix[i][j];
            }
            else {
                cout << setw(3) << " ";
            }
        }
        cout << " |\n";
    }
    cout << "   " << string(18, '-') << "\n\n";
}