#include "Diamond_TicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// Diamond_board implementation
Diamond_board::Diamond_board() : Board<char>(7, 7) {
    for (auto& row : board) {
        for (auto& cell : row) {
            cell = ' ';
        }
    }
}
bool Diamond_board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Check bounds
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position! Row must be 0-6, column 0-6.\n";
        return false;
    }

    // Check if cell is part of diamond
    if (!is_playable_cell(x, y)) {
        cout << "That position is not part of the diamond!\n";
        return false;
    }

    // Check if cell is empty
    if (board[x][y] != ' ') {
        cout << "Cell already occupied!\n";
        return false;
    }

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool Diamond_board::count_three_in_row(char symbol) {
    int dx[4] = {0, 1, 1, 1};
    int dy[4] = {1, 0, 1, -1};

    vector<pair<vector<pair<int,int>>, int>> three_lines;
    vector<pair<vector<pair<int,int>>, int>> four_lines;

    // Check all positions
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 7; y++) {
            if (!is_playable_cell(x, y) || board[x][y] != symbol)
                continue;

            // Check all directions
            for (int d = 0; d < 4; d++) {
                // Check for line of 3
                bool valid_three = true;
                vector<pair<int,int>> line_three;
                for (int step = 0; step < 3; step++) {
                    int nx = x + dx[d] * step;
                    int ny = y + dy[d] * step;

                    if (nx < 0 || nx >= 7 || ny < 0 || ny >= 7 ||
                        !is_playable_cell(nx, ny) ||
                        board[nx][ny] != symbol) {
                        valid_three = false;
                        break;
                    }
                    line_three.push_back({nx, ny});
                }

                if (valid_three) {
                    three_lines.push_back({line_three, d});
                }

                // Check for line of 4
                bool valid_four = true;
                vector<pair<int,int>> line_four;
                for (int step = 0; step < 4; step++) {
                    int nx = x + dx[d] * step;
                    int ny = y + dy[d] * step;

                    if (nx < 0 || nx >= 7 || ny < 0 || ny >= 7 ||
                        !is_playable_cell(nx, ny) ||
                        board[nx][ny] != symbol) {
                        valid_four = false;
                        break;
                    }
                    line_four.push_back({nx, ny});
                }

                if (valid_four) {
                    four_lines.push_back({line_four, d});
                }
            }
        }
    }

    // Check for winning condition: a 3-line and 4-line in different directions
    for (auto& three : three_lines) {
        for (auto& four : four_lines) {
            // Lines must be in different directions
            if (three.second == four.second) continue;

            // They can share at most one cell
            int common_cells = 0;
            for (auto& cell3 : three.first) {
                for (auto& cell4 : four.first) {
                    if (cell3.first == cell4.first && cell3.second == cell4.second) {
                        common_cells++;
                    }
                }
            }

            if (common_cells <= 1) {
                return true;
            }
        }
    }

    return false;
}

bool Diamond_board::count_four_in_row(char symbol) {
    // This is used within count_three_in_row, so just return false here
    return false;
}

bool Diamond_board::is_win(Player<char>* player) {
    return count_three_in_row(player->get_symbol());
}

bool Diamond_board::is_lose(Player<char>* player) {
    // In a two-player game, losing means the opponent wins
    char opponent_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
    return count_three_in_row(opponent_symbol);
}

bool Diamond_board::is_draw(Player<char>* player) {
    // There are 25 playable cells in the diamond: 1+3+5+7+5+3+1 = 25
    if (n_moves < 25) return false;

    // Check if neither player has won
    return !count_three_in_row('X') && !count_three_in_row('O');
}

bool Diamond_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}

// Diamond_UI implementation
pair<int, int> Diamond_UI::display_to_matrix(int display_row, int display_col) const {
    // Map display coordinates to actual matrix coordinates
    return {display_row, display_col};
}


Diamond_UI::Diamond_UI(): ValidatedUI<char>(
    "=== Welcome to DIAMOND Tic-Tac-Toe ===\n"
    "Rules: Complete a 3-in-a-row AND a 4-in-a-row simultaneously to win!\n"
    "The two lines must be in different directions but can share one mark.\n"
    "Board layout (5x5 diamond shape):\n"
    "    Row 0: only column 3\n"
    "    Row 1: columns 2,3,4\n"
    "    Row 2: columns 1,2,3,4,5\n"
    "    Row 3: columns 0-6 \n"
    "    Row 4: columns 1,2,3,4,5\n"
    "    Row 5: columns 2,3,4\n"
    "    Row 6: only column 3",
    3) {
    srand(time(0));
}

Diamond_UI::~Diamond_UI() {
    // Destructor
}

Player<char>* Diamond_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Diamond_UI::get_move(Player<char>* player) {
    Diamond_board* dboard = dynamic_cast<Diamond_board*>(player->get_board_ptr());

    if (player->get_type() == PlayerType::HUMAN) {
        // REMOVED the display_board_matrix call here to prevent double display
        // The GameManager will display the board after the move

        cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";

        int row, col;

        while (true) {
            cout << "Enter row and column (0-6, separated by space): ";

            if (!(cin >> row >> col)) {
                cout << "Invalid input! Enter two numbers.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            // Validate range
            if (row < 0 || row > 6 || col < 0 || col > 6) {
                cout << "Row and column must be between 0 and 6!\n";
                continue;
            }

            // Check if cell is part of diamond
            if (!dboard->is_playable_cell(row, col)) {
                cout << "That position is not in the diamond!\n";
                // Show valid positions for this row
                cout << "Valid columns for row " << row << ": ";
                if (row == 0 || row == 6) {
                    cout << "3";
                } else if (row == 1 || row == 5) {
                    cout << "2, 3, 4";
                } else if (row == 2 || row == 4) {
                    cout << "1, 2, 3, 4, 5";
                } else if (row == 3) {
                    cout << "0, 1, 2, 3, 4, 5, 6";
                }
                cout << "\n";
                continue;
            }

            // Check if cell is empty
            if (dboard->get_cell(row, col) != ' ') {
                cout << "Cell already occupied! Choose another position.\n";
                continue;
            }

            // Valid move
            break;
        }

        return new Move<char>(row, col, player->get_symbol());
    }
    else {
        // COMPUTER PLAYER
        // Get list of all empty playable cells
        vector<pair<int, int>> empty_cells;

        for (int row = 0; row < 7; row++) {
            for (int col = 0; col < 7; col++) {
                if (dboard->is_playable_cell(row, col) &&
                    dboard->get_cell(row, col) == ' ') {
                    empty_cells.push_back({row, col});
                }
            }
        }

        if (empty_cells.empty()) {
            cout << "Computer has no valid moves!\n";
            return new Move<char>(-1, -1, player->get_symbol());
        }

        // Choose random move
        int choice = rand() % empty_cells.size();
        int row = empty_cells[choice].first;
        int col = empty_cells[choice].second;

        cout << "\nComputer plays at (" << row << ", " << col << ")\n";

        return new Move<char>(row, col, player->get_symbol());
    }
}