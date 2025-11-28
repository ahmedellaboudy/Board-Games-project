#include <iostream>
#include <iomanip>
#include <cctype>
#include "infinity_XO.h"

using namespace std;

//--------------------------------------- infinity_Board Implementation

infinity_Board::infinity_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool infinity_Board::update_board(Move<char>* move) {
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
    board[x][y] = toupper(mark);
    move_history.push({x, y});
    n_moves++;

    // CRITICAL: After every 3 moves, remove the oldest mark
    // This means: after moves 3, 6, 9, 12, etc.
    if (n_moves % 3 == 0) {
        remove_oldest_move();
    }

    return true;
}

void infinity_Board::remove_oldest_move() {
    if (!move_history.empty()) {
        auto oldest = move_history.front();
        move_history.pop();

        int x = oldest.first;
        int y = oldest.second;

        // Clear the oldest mark
        board[x][y] = blank_symbol;
        
        cout << "Oldest mark at (" << x << ", " << y << ") has disappeared!\n";
    }
}

bool infinity_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    // Helper lambda to check if three cells are equal and not blank
    auto all_equal = [&](char a, char b, char c) {
        return a == sym && b == sym && c == sym && a != blank_symbol;
    };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        // Check row
        if (all_equal(board[i][0], board[i][1], board[i][2]))
            return true;
        
        // Check column
        if (all_equal(board[0][i], board[1][i], board[2][i]))
            return true;
    }

    // Check main diagonal (top-left to bottom-right)
    if (all_equal(board[0][0], board[1][1], board[2][2]))
        return true;

    // Check anti-diagonal (top-right to bottom-left)
    if (all_equal(board[0][2], board[1][1], board[2][0]))
        return true;

    return false;
}

bool infinity_Board::is_draw(Player<char>* player) {
    // The game can theoretically go on indefinitely in Infinity Tic-Tac-Toe
    // However, we'll consider it a draw after a reasonable number of moves
    // Let's say 50 moves without a winner
    return (n_moves >= 50 && !is_win(player));
}

bool infinity_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- infinity_UI Implementation

infinity_UI::infinity_UI() : ValidatedUI<char>("=== Welcome to Infinity Tic-Tac-Toe ===\n"
    "Rules: After every 3 moves, the oldest mark disappears!\n"
    "Win by getting 3 in a row before your marks vanish.", 3) {}

Player<char>* infinity_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* infinity_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        auto pos = get_validated_position(
            "\n" + player->get_name() + " (" + string(1, player->get_symbol()) +
            "), enter your move (row column 0-2): ",
            3,  // max_row (0-2 means pass 3)
            3,  // max_col (0-2 means pass 3)
            player->get_board_ptr(),
            '.'
        );
        x = pos.first;
        y = pos.second;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Random valid move
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (player->get_board_ptr()->get_cell(x, y) != '.');

        cout << "\n" << player->get_name() << " (" << player->get_symbol()
             << ") plays at: " << x << " " << y << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}