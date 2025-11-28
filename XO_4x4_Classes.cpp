#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <vector>
#include "MisereTicTacToe.h"

using namespace std;

// ----------------- Misère 3x3 Board -----------------
MisereTicTacToe_board::MisereTicTacToe_board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;


}

bool MisereTicTacToe_board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) return false;

    if (mark == '.') {
        board[x][y] = blank_symbol;
    } else {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    return false;
}

// ----------------- Misère Win (you lose if 3 in a row) -----------------
bool MisereTicTacToe_board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();
    for (int i = 0; i < rows; ++i)
        if (board[i][0] == sym && board[i][1] == sym && board[i][2] == sym) return true;

    for (int j = 0; j < columns; ++j)
        if (board[0][j] == sym && board[1][j] == sym && board[2][j] == sym) return true;

    if (board[0][0] == sym && board[1][1] == sym && board[2][2] == sym) return true;
    if (board[0][2] == sym && board[1][1] == sym && board[2][0] == sym) return true;

    return false;
}

bool MisereTicTacToe_board::is_draw(Player<char>* player) {
    return (n_moves >= 9 && !is_win(player));
}

bool MisereTicTacToe_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

// ----------------- Adjacent move -----------------
bool MisereTicTacToe_board::is_valid_adjacent_move(int from_x, int from_y, int to_x, int to_y) {
    if (from_x < 0 || from_x >= rows || from_y < 0 || from_y >= columns ||
        to_x < 0 || to_x >= rows || to_y < 0 || to_y >= columns) return false;

    if (board[from_x][from_y] == blank_symbol || board[to_x][to_y] != blank_symbol) return false;

    int dx = abs(from_x - to_x);
    int dy = abs(from_y - to_y);
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
}

vector<Move<char>*> MisereTicTacToe_board::get_possible_moves(Player<char>* player) {
    vector<Move<char>*> moves;
    char symbol = player->get_symbol();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] == symbol) {
                int directions[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
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

// ----------------- Misère UI -----------------
MisereTicTacToeUI::MisereTicTacToeUI() : UI<char>("Welcome to Misère 3x3 X-O Game", 3) {}
MisereTicTacToeUI::~MisereTicTacToeUI() {}

Player<char>* MisereTicTacToeUI::create_player(string& name, char symbol, PlayerType type) {
    while (type != PlayerType::HUMAN && type != PlayerType::COMPUTER) {
        cout << "Invalid type! Please choose 1 (Human) or 2 (Computer): ";
        int t; cin >> t;
        type = (t == 1 ? PlayerType::HUMAN : (t == 2 ? PlayerType::COMPUTER : type));
    }
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* MisereTicTacToeUI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::COMPUTER) {
        MisereTicTacToe_board* board = dynamic_cast<MisereTicTacToe_board*>(player->get_board_ptr());
        char symbol = player->get_symbol();
        for (int i = 0; i < board->get_rows(); ++i)
            for (int j = 0; j < board->get_columns(); ++j)
                if (board->get_board_matrix()[i][j] == '.')
                    return new Move<char>(i, j, symbol);
    }
    return get_move_with_source(player);
}

Move<char>* MisereTicTacToeUI::get_move_with_source(Player<char>* player) {
    MisereTicTacToe_board* board = dynamic_cast<MisereTicTacToe_board*>(player->get_board_ptr());
    int to_x, to_y;
    int rows = board->get_rows();
    int columns = board->get_columns();

    cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";

    while (true) {
        cout << "Enter x y of your move (0-" << rows-1 << "): ";
        cin >> to_x >> to_y;

        if (cin.fail() || to_x < 0 || to_x >= rows || to_y < 0 || to_y >= columns ||
            board->get_board_matrix()[to_x][to_y] != '.') {
            cin.clear(); cin.ignore(10000,'\n');
            cout << "Invalid move! Try again.\n";
            continue;
        }

        return new Move<char>(to_x, to_y, player->get_symbol());
    }
}
