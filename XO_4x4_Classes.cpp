#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <vector>
#include "XO_4x4_Classes.h"

using namespace std;

//--------------------------------------- XO_4x4_Board Implementation

XO_4x4_Board::XO_4x4_Board() : Board(4, 4) {
    // Initialize board with starting positions
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    // Set initial positions for X and O
    // Player X starts at top and bottom rows
    board[0][0] = 'X'; board[0][2] = 'X';
    board[3][1] = 'X'; board[3][3] = 'X';

    // Player O starts at top and bottom rows  
    board[0][1] = 'O'; board[0][3] = 'O';
    board[3][0] = 'O'; board[3][2] = 'O';
}

bool XO_4x4_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // For 4x4 X-O, we need to handle moving existing tokens
    // This simplified version assumes the move contains both source and destination
    // In a complete implementation, we would need to track token positions

    // Validate move coordinates
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }

    // Check if cell is empty
    if (board[x][y] == blank_symbol) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }

    return false;
}

bool XO_4x4_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    // Check for 3 in a row in rows
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns - 2; ++j) {
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym)
                return true;
        }
    }

    // Check for 3 in a row in columns
    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i < rows - 2; ++i) {
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym)
                return true;
        }
    }

    // Check for 3 in a row in diagonals (top-left to bottom-right)
    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 0; j < columns - 2; ++j) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym)
                return true;
        }
    }

    // Check for 3 in a row in diagonals (top-right to bottom-left)
    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 2; j < columns; ++j) {
            if (board[i][j] == sym && board[i + 1][j - 1] == sym && board[i + 2][j - 2] == sym)
                return true;
        }
    }

    return false;
}

bool XO_4x4_Board::is_draw(Player<char>* player) {
    // For 4x4 X-O, a draw occurs when no player can form 3 in a row
    // This is a simplified check - in reality, we'd need to check if no moves can lead to win
    return (n_moves >= 16 && !is_win(player));
}

bool XO_4x4_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool XO_4x4_Board::is_valid_adjacent_move(int from_x, int from_y, int to_x, int to_y) {
    // Check if coordinates are valid
    if (from_x < 0 || from_x >= rows || from_y < 0 || from_y >= columns ||
        to_x < 0 || to_x >= rows || to_y < 0 || to_y >= columns) {
        return false;
    }

    // Check if source has a token and destination is empty
    if (board[from_x][from_y] == blank_symbol || board[to_x][to_y] != blank_symbol) {
        return false;
    }

    // Check if move is to adjacent cell (horizontal or vertical)
    int dx = abs(from_x - to_x);
    int dy = abs(from_y - to_y);

    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

vector<Move<char>*> XO_4x4_Board::get_possible_moves(Player<char>* player) {
    vector<Move<char>*> moves;
    char symbol = player->get_symbol();

    // Find all player's tokens and their possible moves
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == symbol) {
                // Check all adjacent cells
                int directions[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
                for (auto& dir : directions) {
                    int new_i = i + dir[0];
                    int new_j = j + dir[1];
                    if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < columns &&
                        board[new_i][new_j] == blank_symbol) {
                        moves.push_back(new Move<char>(new_i, new_j, symbol));
                    }
                }
            }
        }
    }

    return moves;
}

//--------------------------------------- XO_4x4_UI Implementation

XO_4x4_UI::XO_4x4_UI() : UI<char>("Welcome to FCAI 4x4 X-O Game", 3) {}

Player<char>* XO_4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* XO_4x4_UI::get_move(Player<char>* player) {
    // For computer player, choose random valid move
    if (player->get_type() == PlayerType::COMPUTER) {
        XO_4x4_Board* board = dynamic_cast<XO_4x4_Board*>(player->get_board_ptr());
        if (board) {
            vector<Move<char>*> possible_moves = board->get_possible_moves(player);
            if (!possible_moves.empty()) {
                int random_index = rand() % possible_moves.size();
                Move<char>* selected_move = possible_moves[random_index];

                // Clean up other moves
                for (int i = 0; i < possible_moves.size(); ++i) {
                    if (i != random_index) {
                        delete possible_moves[i];
                    }
                }

                return selected_move;
            }
        }

        // Fallback: random empty cell
        int x, y;
        do {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        } while (player->get_board_ptr()->get_board_matrix()[x][y] != '.');

        return new Move<char>(x, y, player->get_symbol());
    }

    // For human player, use the enhanced move method
    return get_move_with_source(player);
}

Move<char>* XO_4x4_UI::get_move_with_source(Player<char>* player) {
    int from_x, from_y, to_x, to_y;
    XO_4x4_Board* board = dynamic_cast<XO_4x4_Board*>(player->get_board_ptr());

    if (!board) {
        // Fallback to simple move
        cout << "\nPlease enter your move x and y (0 to 3): ";
        cin >> to_x >> to_y;
        return new Move<char>(to_x, to_y, player->get_symbol());
    }

    cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";

    while (true) {
        cout << "Enter source coordinates (x y) of your token to move: ";
        cin >> from_x >> from_y;

        cout << "Enter destination coordinates (x y) to move to: ";
        cin >> to_x >> to_y;

        if (board->is_valid_adjacent_move(from_x, from_y, to_x, to_y) &&
            board->get_board_matrix()[from_x][from_y] == player->get_symbol()) {

            // Create move for destination
            Move<char>* move = new Move<char>(to_x, to_y, player->get_symbol());

            // Also update the source to be empty (this would need additional handling)
            // In a complete implementation, we'd need to modify the board directly
            // or extend the Move class to handle source coordinates

            return move;
        }
        else {
            cout << "Invalid move! Please make sure:\n";
            cout << "- Source has your token\n";
            cout << "- Destination is empty and adjacent (horizontal/vertical)\n";
            cout << "- Coordinates are between 0 and 3\n";
        }
    }
}