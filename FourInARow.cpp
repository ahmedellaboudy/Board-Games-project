#include "FourInARow.h"
#include "FourInARow_AI_Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

//--------------------------------------- FourInARow_Board Implementation

FourInARow_Board::FourInARow_Board() : Board(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

int FourInARow_Board::find_lowest_row(int col) {
    for (int row = rows - 1; row >= 0; row--) {
        if (board[row][col] == blank_symbol) {
            return row;
        }
    }
    return -1;
}

bool FourInARow_Board::update_board(Move<char>* move) {
    int col = move->get_y();
    char mark = move->get_symbol();

    if (col < 0 || col >= columns) {
        cout << "Invalid column! Please choose between 0 and " << (columns - 1) << "\n";
        return false;
    }

    int row = find_lowest_row(col);

    if (row == -1) {
        cout << "Column " << col << " is full! Choose another column.\n";
        return false;
    }

    board[row][col] = mark;
    n_moves++;
    return true;
}

bool FourInARow_Board::check_horizontal(char symbol) {
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
    // Diagonal (bottom-left to top-right)
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

    // Diagonal (top-left to bottom-right)
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
    return false;
}

bool FourInARow_Board::is_draw(Player<char>* player) {
    if (n_moves < rows * columns) return false;
    return !check_four_in_row('X') && !check_four_in_row('O');
}

bool FourInARow_Board::game_is_over(Player<char>* player) {
    return check_four_in_row('X') ||
           check_four_in_row('O') ||
           (n_moves >= rows * columns);
}

//--------------------------------------- FourInARow_UI Implementation

FourInARow_UI::FourInARow_UI() : ValidatedUI<char>(
    "=== Welcome to Four-in-a-Row ===\n"
    "Rules: Get four marks in a row to win!\n"
    "Choose a column (0-6) and your piece will fall to the bottom.", 3) {}

PlayerType FourInARow_UI::get_player_type_choice(string player_label, const vector<string>& options) {
    cout << "Choose " << player_label << " type:\n";
    for (size_t i = 0; i < options.size(); ++i)
        cout << i + 1 << ". " << options[i] << "\n";

    int choice;
    while (true) {
        cout << "Enter choice: ";
        if (cin >> choice) {
            if (choice >= 1 && choice <= (int)options.size()) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (choice == 1) return PlayerType::HUMAN;
                if (choice == 2) return PlayerType::AI;

                return PlayerType::HUMAN;
            }
            cout << "Invalid choice! Please enter a number between 1 and "
                 << options.size() << ".\n";
        } else {
            cout << "Invalid input! Please enter a number.\n";
            clear_input_buffer();
        }
    }
}

Player<char>** FourInARow_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "AI (Smart)" };

    string nameX = get_player_name("Player X");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    string nameO = get_player_name("Player O");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

Player<char>* FourInARow_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::AI) {
        cout << "Creating AI player: " << name << " (" << symbol << ")\n";
        return new FourInARow_AI_Player(name, symbol);
    } else {
        cout << "Creating human player: " << name << " (" << symbol << ")\n";
        return new Player<char>(name, symbol, type);
    }
}

Move<char>* FourInARow_UI::get_move(Player<char>* player) {
    int col;

    if (player->get_type() == PlayerType::HUMAN) {
        col = get_validated_int(
            "\n" + player->get_name() + " (" + string(1, player->get_symbol()) +
            "), choose a column (0-6): ",
            0, 6
        );
    }
    else if (player->get_type() == PlayerType::AI) {
        FourInARow_AI_Player* ai_player = dynamic_cast<FourInARow_AI_Player*>(player);

        cout << "\nAI " << player->get_name() << " is thinking...\n";
        col = ai_player->get_best_column();

        cout << "AI " << player->get_name() << " (" << player->get_symbol()
             << ") plays column: " << col << endl;
    }

    return new Move<char>(0, col, player->get_symbol());
}