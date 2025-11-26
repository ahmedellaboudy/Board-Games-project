#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <vector>
#include "XO_4x4_Classes.h"

using namespace std;

XO_4x4_Board::XO_4x4_Board() : Board(4, 4) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    board[0][0] = 'X'; board[0][2] = 'X';
    board[3][1] = 'X'; board[3][3] = 'X';

    board[0][1] = 'O'; board[0][3] = 'O';
    board[3][0] = 'O'; board[3][2] = 'O';
}

bool XO_4x4_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }


    if (board[x][y] == blank_symbol) {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }

    return false;
}

bool XO_4x4_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns - 2; ++j) {
            if (board[i][j] == sym && board[i][j + 1] == sym && board[i][j + 2] == sym)
                return true;
        }
    }

    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i < rows - 2; ++i) {
            if (board[i][j] == sym && board[i + 1][j] == sym && board[i + 2][j] == sym)
                return true;
        }
    }

    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 0; j < columns - 2; ++j) {
            if (board[i][j] == sym && board[i + 1][j + 1] == sym && board[i + 2][j + 2] == sym)
                return true;
        }
    }

    for (int i = 0; i < rows - 2; ++i) {
        for (int j = 2; j < columns; ++j) {
            if (board[i][j] == sym && board[i + 1][j - 1] == sym && board[i + 2][j - 2] == sym)
                return true;
        }
    }

    return false;
}

bool XO_4x4_Board::is_draw(Player<char>* player) {
    return (n_moves >= 16 && !is_win(player));
}

bool XO_4x4_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool XO_4x4_Board::is_valid_adjacent_move(int from_x, int from_y, int to_x, int to_y) {
    if (from_x < 0 || from_x >= rows || from_y < 0 || from_y >= columns ||
        to_x < 0 || to_x >= rows || to_y < 0 || to_y >= columns) {
        return false;
    }

    if (board[from_x][from_y] == blank_symbol || board[to_x][to_y] != blank_symbol) {
        return false;
    }
    int dx = abs(from_x - to_x);
    int dy = abs(from_y - to_y);

    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

vector<Move<char>*> XO_4x4_Board::get_possible_moves(Player<char>* player) {
    vector<Move<char>*> moves;
    char symbol = player->get_symbol();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == symbol) {
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
XO_4x4_UI::XO_4x4_UI() : UI<char>("Welcome to FCAI 4x4 X-O Game", 3) {}

Player<char>* XO_4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* XO_4x4_UI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::COMPUTER) {
        XO_4x4_Board* board = dynamic_cast<XO_4x4_Board*>(player->get_board_ptr());
        if (board) {
            vector<Move<char>*> possible_moves = board->get_possible_moves(player);
            if (!possible_moves.empty()) {
                int random_index = rand() % possible_moves.size();
                Move<char>* selected_move = possible_moves[random_index];
                for (int i = 0; i < possible_moves.size(); ++i) {
                    if (i != random_index) {
                        delete possible_moves[i];
                    }
                }

                return selected_move;
            }
        }
        int x, y;
        do {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        } while (player->get_board_ptr()->get_board_matrix()[x][y] != '.');

        return new Move<char>(x, y, player->get_symbol());
    }
    return get_move_with_source(player);
}

Move<char>* XO_4x4_UI::get_move_with_source(Player<char>* player) {
    int from_x, from_y, to_x, to_y;
    XO_4x4_Board* board = dynamic_cast<XO_4x4_Board*>(player->get_board_ptr());

    if (!board) {
        cout << "\nPlease enter your move x and y (0 to 3): ";
        cin >> to_x >> to_y;
        return new Move<char>(to_x, to_y, player->get_symbol());
    }

    cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";
    while (true) {
        try {
            cout << "Enter source coordinates (x y) of your token to move: ";
            cin >> from_x >> from_y;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw invalid_argument("Invalid input! Please enter numbers only.");
            }
            cout << "Enter destination coordinates (x y) to move to: ";
            cin >> to_x >> to_y;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw invalid_argument("Invalid input! Please enter numbers only.");
            }


            if (board->is_valid_adjacent_move(from_x, from_y, to_x, to_y) &&
                board->get_board_matrix()[from_x][from_y] == player->get_symbol()) {

                Move<char>* move = new Move<char>(to_x, to_y, player->get_symbol());

                return move;
            }
            else {
                throw invalid_argument("Invalid move! Please make sure:\n"
                    "- Source has your token\n"
                    "- Destination is empty and adjacent (horizontal/vertical)\n"
                    "- Coordinates are between 0 and 3");
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cout << "Please try again.\n";
        }

    }
}