#include "MisereTicTacToe.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//--------------------------------------- Misere_Board Implementation

Misere_Board::Misere_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Misere_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move position
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position! Please choose between (0-2, 0-2)\n";
        return false;
    }

    // Check if cell is empty
    if (board[x][y] != blank_symbol) {
        cout << "Cell is already occupied! Choose another cell.\n";
        return false;
    }

    // Place the mark
    board[x][y] = mark;
    n_moves++;
    return true;
}

bool Misere_Board::has_three_in_row(char symbol) {
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

    // Check main diagonal (top-left to bottom-right)
    if (board[0][0] == symbol &&
        board[1][1] == symbol &&
        board[2][2] == symbol) {
        return true;
    }

    // Check anti-diagonal (top-right to bottom-left)
    if (board[0][2] == symbol &&
        board[1][1] == symbol &&
        board[2][0] == symbol) {
        return true;
    }

    return false;
}

bool Misere_Board::is_win(Player<char>* player) {
    // In Misere: You WIN if your OPPONENT gets three-in-a-row
    char opponent_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
    return has_three_in_row(opponent_symbol);
}

bool Misere_Board::is_lose(Player<char>* player) {
    // In Misere: You LOSE if YOU get three-in-a-row
    return has_three_in_row(player->get_symbol());
}

bool Misere_Board::is_draw(Player<char>* player) {
    // Draw if board is full and nobody got three-in-a-row
    if (n_moves < 9) return false;

    return !has_three_in_row('X') && !has_three_in_row('O');
}

bool Misere_Board::game_is_over(Player<char>* player) {
    // Game ends if someone got three-in-a-row OR board is full
    return has_three_in_row('X') || has_three_in_row('O') || (n_moves >= 9);
}

//--------------------------------------- Misere_UI Implementation

Misere_UI::Misere_UI() : ValidatedUI<char>(
    "=== Welcome to Misere Tic-Tac-Toe ===\n"
    "Rules: AVOID getting three-in-a-row!\n"
    "If you get three-in-a-row, you LOSE!", 3) {}

Player<char>* Misere_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Misere_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        // Use validated input from ValidatedUI
        auto pos = get_validated_position(
            "\n" + player->get_name() + " (" + string(1, player->get_symbol()) +
            "), enter your move (row column 0-2): ",
            3,
            3,
            player->get_board_ptr(),
            ' '
        );
        x = pos.first;
        y = pos.second;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Computer makes random valid moves
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (player->get_board_ptr()->get_cell(x, y) != ' ');

        cout << "\n" << player->get_name() << " (" << player->get_symbol()
             << ") plays at: " << x << " " << y << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}
