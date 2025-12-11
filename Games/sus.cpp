//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>
#include "sus.h"
#include "SUS_AI_Player.h"

using namespace std;

//--------------------------------------- SUS_Board Implementation

SUS_Board::SUS_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol) && (mark == 'S' || mark == 'U')) {

        int sequences_before = count_sus_sequences('S');

        n_moves++;
        board[x][y] = toupper(mark);
        int sequences_after = count_sus_sequences('S');

        int new_sequences = sequences_after - sequences_before;
        if (new_sequences > 0) {
            if (mark == 'S') {
                player1_score += new_sequences;
            } else {
                player2_score += new_sequences;
            }
        }

        return true;
    }
    return false;
}

int SUS_Board::count_sus_sequences(char symbol) {
    int count = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= columns - 3; ++j) {
            if (board[i][j] == 'S' && board[i][j+1] == 'U' && board[i][j+2] == 'S') {
                count++;
            }
        }
    }

    for (int j = 0; j < columns; ++j) {
        for (int i = 0; i <= rows - 3; ++i) {
            if (board[i][j] == 'S' && board[i+1][j] == 'U' && board[i+2][j] == 'S') {
                count++;
            }
        }
    }

    if (board[0][0] == 'S' && board[1][1] == 'U' && board[2][2] == 'S')
        count++;

    if (board[0][2] == 'S' && board[1][1] == 'U' && board[2][0] == 'S')
        count++;

    return count;
}

bool SUS_Board::is_win(Player<char>* player) {
    if (n_moves < 9) return false;

    if (player->get_symbol() == 'S') {
        return player1_score > player2_score;
    } else {
        return player2_score > player1_score;
    }
}

bool SUS_Board::is_draw(Player<char>* player) {
    if (n_moves < 9) return false;
    return (player1_score == player2_score);
}

bool SUS_Board::game_is_over(Player<char>* player) {
    return (n_moves == 9);
}

//--------------------------------------- SUS_UI Implementation

SUS_UI::SUS_UI() : ValidatedUI<char>("Welcome to SUS Game!", 3) {
    cout << "\nGame Rules:\n";
    cout << "- Players take turns placing 'S' or 'U' on a 3x3 grid\n";
    cout << "- Each player must use the same letter throughout the game\n";
    cout << "- Score points by forming 'S-U-S' sequences (horizontally, vertically, or diagonally)\n";
    cout << "- The player with the most S-U-S sequences when the board is full wins!\n\n";
}

PlayerType SUS_UI::get_player_type_choice(string player_label, const vector<string>& options) {
    cout << "Choose " << player_label << " type:\n";
    for (size_t i = 0; i < options.size(); ++i)
        cout << i + 1 << ". " << options[i] << "\n";

    int choice;
    while (true) {
        cout << "Enter choice: ";
        if (cin >> choice) {
            if (choice >= 1 && choice <= (int)options.size()) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // Only 2 options: Human or AI
                if (choice == 1) return PlayerType::HUMAN;
                if (choice == 2) return PlayerType::AI;

                return PlayerType::HUMAN; // Default
            }
            cout << "Invalid choice! Please enter a number between 1 and "
                 << options.size() << ".\n";
        } else {
            cout << "Invalid input! Please enter a number.\n";
            clear_input_buffer();
        }
    }
}

Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "AI (Smart)" };

    string nameX = get_player_name("Player 1");
    PlayerType typeX = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(nameX, 'S', typeX);

    string nameO = get_player_name("Player 2");
    PlayerType typeO = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(nameO, 'U', typeO);

    return players;
}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::AI) {
        cout << "Creating AI player: " << name << " (uses '" << symbol << "')\n";
        char opponent_symbol = (symbol == 'S') ? 'U' : 'S';
        return new SUS_AI_Player(name, symbol, opponent_symbol);
    } else {
        cout << "Creating human player: " << name << " (uses '" << symbol << "')\n";
        return new Player<char>(name, symbol, type);
    }
}

Move<char>* SUS_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (using '"
             << player->get_symbol() << "')\n";

        auto pos = get_validated_position(
            "Enter row and column (0-2): ",
            3, 3,
            player->get_board_ptr(),
            '.'
        );

        x = pos.first;
        y = pos.second;
    }
    else if (player->get_type() == PlayerType::AI) {
        // AI Smart Player
        SUS_AI_Player* ai_player = dynamic_cast<SUS_AI_Player*>(player);
        SUS_Board* sus_board = dynamic_cast<SUS_Board*>(player->get_board_ptr());

        auto scores = sus_board->get_scores();
        int ai_score = (player->get_symbol() == 'S') ? scores.first : scores.second;
        int opp_score = (player->get_symbol() == 'S') ? scores.second : scores.first;

        ScoredMove best = ai_player->get_best_move(ai_score, opp_score);

        x = best.x;
        y = best.y;

        cout << "AI " << player->get_name() << " plays at ("
             << x << ", " << y << ")\n";
    }

    return new Move<char>(x, y, player->get_symbol());
}

void SUS_UI::display_scores(int p1_score, int p2_score) {
    cout << "    CURRENT SCORES      \n";
    cout << "Player 1 (S): " << setw(2) << p1_score << " sequences\n";
    cout << "Player 2 (U): " << setw(2) << p2_score << " sequences\n";
}
