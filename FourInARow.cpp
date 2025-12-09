#include "FourInARow.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//--------------------------------------- FourInARow_Board Implementation

FourInARow_Board::FourInARow_Board() : Board(6, 7) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

int FourInARow_Board::find_lowest_row(int col) {
    // Start from bottom row (row 5) and go up
    for (int row = rows - 1; row >= 0; row--) {
        if (board[row][col] == blank_symbol) {
            return row;
        }
    }
    return -1; // Column is full
}

bool FourInARow_Board::update_board(Move<char>* move) {
    int col = move->get_y(); // Column chosen by player
    char mark = move->get_symbol();

    // Validate column
    if (col < 0 || col >= columns) {
        cout << "Invalid column! Please choose between 0 and " << (columns - 1) << "\n";
        return false;
    }

    // Find lowest available row in this column
    int row = find_lowest_row(col);
    
    if (row == -1) {
        cout << "Column " << col << " is full! Choose another column.\n";
        return false;
    }

    // Place the mark
    board[row][col] = mark;
    n_moves++;
    return true;
}

bool FourInARow_Board::check_horizontal(char symbol) {
    // Check each row for four consecutive marks
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col <= columns - 4; col++) {
            if (board[row][col] == symbol &&
                board[row][col + 1] == symbol &&
                board[row][col + 2] == symbol &&
                board[row][col + 3] == symbol) {
                return true;
            }
        }
    }
    return false;
}

bool FourInARow_Board::check_vertical(char symbol) {
    // Check each column for four consecutive marks
    for (int col = 0; col < columns; col++) {
        for (int row = 0; row <= rows - 4; row++) {
            if (board[row][col] == symbol &&
                board[row + 1][col] == symbol &&
                board[row + 2][col] == symbol &&
                board[row + 3][col] == symbol) {
                return true;
            }
        }
    }
    return false;
}

bool FourInARow_Board::check_diagonal(char symbol) {
    // Check diagonals (bottom-left to top-right)
    for (int row = 3; row < rows; row++) {
        for (int col = 0; col <= columns - 4; col++) {
            if (board[row][col] == symbol &&
                board[row - 1][col + 1] == symbol &&
                board[row - 2][col + 2] == symbol &&
                board[row - 3][col + 3] == symbol) {
                return true;
            }
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int row = 0; row <= rows - 4; row++) {
        for (int col = 0; col <= columns - 4; col++) {
            if (board[row][col] == symbol &&
                board[row + 1][col + 1] == symbol &&
                board[row + 2][col + 2] == symbol &&
                board[row + 3][col + 3] == symbol) {
                return true;
            }
        }
    }

    return false;
}

bool FourInARow_Board::check_four_in_row(char symbol) {
    return check_horizontal(symbol) || 
           check_vertical(symbol) || 
           check_diagonal(symbol);
}

bool FourInARow_Board::is_win(Player<char>* player) {
    return check_four_in_row(player->get_symbol());
}

bool FourInARow_Board::is_lose(Player<char>* player) {
    return false; // No lose condition in this game
}

bool FourInARow_Board::is_draw(Player<char>* player) {
    // Draw if board is full (42 moves) and nobody won
    if (n_moves < rows * columns) return false;

    return !check_four_in_row('X') && !check_four_in_row('O');
}

bool FourInARow_Board::game_is_over(Player<char>* player) {
    // Game ends if someone won or board is full
    return check_four_in_row('X') || 
           check_four_in_row('O') || 
           (n_moves >= rows * columns);
}

//--------------------------------------- FourInARow_UI Implementation

FourInARow_UI::FourInARow_UI() : ValidatedUI<char>(
    "=== Welcome to Four-in-a-Row ===\n"
    "Rules: Get four marks in a row to win!\n"
    "Choose a column (0-6) and your piece will fall to the bottom.", 3) {}

Player<char>* FourInARow_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* FourInARow_UI::get_move(Player<char>* player) {
    int col;

    if (player->get_type() == PlayerType::HUMAN) {
        // Get column input with validation
        col = get_validated_int(
            "\n" + player->get_name() + " (" + string(1, player->get_symbol()) +
            "), choose a column (0-6): ",
            0,  // min column
            6   // max column
        );
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Computer chooses a random valid column
        FourInARow_Board* board = dynamic_cast<FourInARow_Board*>(player->get_board_ptr());
        
        // Find columns that aren't full
        vector<int> valid_columns;
        for (int c = 0; c < 7; c++) {
            if (board->get_cell(0, c) == ' ') {
                valid_columns.push_back(c);
            }
        }

        if (valid_columns.empty()) {
            // This shouldn't happen, but just in case
            col = 0;
        } else {
            col = valid_columns[rand() % valid_columns.size()];
        }

        cout << "\n" << player->get_name() << " (" << player->get_symbol()
             << ") plays column: " << col << endl;
    }

    // Return move with column (row doesn't matter, will be calculated in update_board)
    return new Move<char>(0, col, player->get_symbol());
}