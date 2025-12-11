#include "Memory_TicTacToe.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// ==================== Memory_Board Implementation ====================

Memory_Board::Memory_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Memory_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position! Please choose between (0-2, 0-2)\n";
        return false;
    }

    if (board[x][y] != blank_symbol) {
        cout << "Cell is already occupied! Choose another cell.\n";
        return false;
    }

    board[x][y] = mark;
    n_moves++;
    return true;
}

bool Memory_Board::has_three_in_row(char symbol) {
    // Check rows
    for (int i = 0; i < rows; i++) {
        if (board[i][0] == symbol &&
            board[i][1] == symbol &&
            board[i][2] == symbol) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < columns; j++) {
        if (board[0][j] == symbol &&
            board[1][j] == symbol &&
            board[2][j] == symbol) {
            return true;
        }
    }

    // Check main diagonal
    if (board[0][0] == symbol &&
        board[1][1] == symbol &&
        board[2][2] == symbol) {
        return true;
    }

    // Check anti-diagonal
    if (board[0][2] == symbol &&
        board[1][1] == symbol &&
        board[2][0] == symbol) {
        return true;
    }

    return false;
}

bool Memory_Board::is_win(Player<char>* player) {
    return has_three_in_row(player->get_symbol());
}

bool Memory_Board::is_lose(Player<char>* player) {
    char opponent_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
    return has_three_in_row(opponent_symbol);
}

bool Memory_Board::is_draw(Player<char>* player) {
    if (n_moves < 9) return false;
    return !has_three_in_row('X') && !has_three_in_row('O');
}

bool Memory_Board::game_is_over(Player<char>* player) {
    return has_three_in_row('X') || has_three_in_row('O') || (n_moves >= 9);
}

// ==================== Fake_Board Implementation ====================

Fake_Board::Fake_Board() : Board(3, 3) {
    // Initialize all cells with blank (space)
    for (auto& row : board)
        for (auto& cell : row)
            cell = ' ';  // Start blank
}

bool Fake_Board::update_board(Move<char>* move) {
    // When a move is made, show '?' instead of the actual symbol
    int x = move->get_x();
    int y = move->get_y();

    if (x >= 0 && x < rows && y >= 0 && y < columns) {
        board[x][y] = '?';  // Show '?' for any move
        n_moves++;
        return true;
    }
    return false;
}

bool Fake_Board::is_win(Player<char>*) {
    return false;
}

bool Fake_Board::is_lose(Player<char>*) {
    return false;
}

bool Fake_Board::is_draw(Player<char>*) {
    return false;
}

bool Fake_Board::game_is_over(Player<char>*) {
    return false;
}

// ==================== Memory_UI Implementation ====================

Memory_UI::Memory_UI() : ValidatedUI<char>(
    "=== Welcome to Memory Tic-Tac-Toe ===\n"
    "Rules: Cells will show '?' when occupied.\n"
    "Remember which symbol is where!", 3) {}

Player<char>* Memory_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Memory_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        auto pos = get_validated_position(
            "\n" + player->get_name() + " (" + string(1, player->get_symbol()) +
            "), enter your move (row column 0-2): ",
            3, 3,
            player->get_board_ptr(),
            ' '
        );
        x = pos.first;
        y = pos.second;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (player->get_board_ptr()->get_cell(x, y) != ' ');

        cout << "\n" << player->get_name() << " (" << player->get_symbol()
             << ") plays at: " << x << " " << y << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}
