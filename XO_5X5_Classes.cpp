#include "XO_5x5_Classes.h"
#include <iostream>
#include <iomanip>

using namespace std;

//=====================================================
// XO_5x5_Board Implementation
//=====================================================

XO_5x5_Board::XO_5x5_Board() : Board(5, 5) {
    // Initialize empty board
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }
}

bool XO_5x5_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Check if move is valid
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position! Please choose between (0-4, 0-4)\n";
        return false;
    }

    if (board[x][y] != ' ') {
        cout << "Cell is already occupied! Choose another cell.\n";
        return false;
    }

    // Update board
    board[x][y] = symbol;
    n_moves++;
    return true;
}

int XO_5x5_Board::count_three_in_row(char symbol) {
    int count = 0;

    // Check horizontal sequences
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= columns - 3; j++) {
            if (board[i][j] == symbol &&
                board[i][j + 1] == symbol &&
                board[i][j + 2] == symbol) {
                count++;
            }
        }
    }

    // Check vertical sequences
    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == symbol &&
                board[i + 1][j] == symbol &&
                board[i + 2][j] == symbol) {
                count++;
            }
        }
    }

    // Check diagonal (\) sequences
    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 0; j <= columns - 3; j++) {
            if (board[i][j] == symbol &&
                board[i + 1][j + 1] == symbol &&
                board[i + 2][j + 2] == symbol) {
                count++;
            }
        }
    }

    // Check anti-diagonal (/) sequences
    for (int i = 0; i <= rows - 3; i++) {
        for (int j = 2; j < columns; j++) {
            if (board[i][j] == symbol &&
                board[i + 1][j - 1] == symbol &&
                board[i + 2][j - 2] == symbol) {
                count++;
            }
        }
    }

    return count;
}

bool XO_5x5_Board::is_win(Player<char>* player) {
    if (n_moves < 24) return false;

    char current_symbol = player->get_symbol();
    char opponent_symbol = (current_symbol == 'X') ? 'O' : 'X';

    int current_score = count_three_in_row(current_symbol);
    int opponent_score = count_three_in_row(opponent_symbol);

    return current_score > opponent_score;
}

bool XO_5x5_Board::is_draw(Player<char>* player) {
    if (n_moves < 24) return false;

    char current_symbol = player->get_symbol();
    char opponent_symbol = (current_symbol == 'X') ? 'O' : 'X';

    int current_score = count_three_in_row(current_symbol);
    int opponent_score = count_three_in_row(opponent_symbol);

    return current_score == opponent_score;
}

bool XO_5x5_Board::game_is_over(Player<char>* player) {
    return n_moves >= 24;
}

void XO_5x5_Board::display_scores(Player<char>* player1, Player<char>* player2) {
    int score1 = count_three_in_row(player1->get_symbol());
    int score2 = count_three_in_row(player2->get_symbol());

    cout << "\n=== Final Scores ===" << endl;
    cout << player1->get_name() << " (" << player1->get_symbol() << "): " << score1 << " three-in-a-rows" << endl;
    cout << player2->get_name() << " (" << player2->get_symbol() << "): " << score2 << " three-in-a-rows" << endl;
}

//=====================================================
// XO_5x5_UI Implementation
//=====================================================

XO_5x5_UI::XO_5x5_UI() : ValidatedUI<char>("=== 5x5 Three-in-a-Row Game ===", 3) {}

Move<char>* XO_5x5_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        auto pos = get_validated_position(
            player->get_name() + " (" + player->get_symbol() +
            "), enter your move (row column): ",
            5,
            5,
            player->get_board_ptr(),
            ' '
        );
        x = pos.first;
        y = pos.second;
    }
    else {
        x = rand() % 5;
        y = rand() % 5;
        cout << player->get_name() << " (" << player->get_symbol()
             << ") plays at: " << x << " " << y << endl;
    }

    return new Move<char>(x, y, player->get_symbol());
}

Player<char>** XO_5x5_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player 1 (uses X) ");
    PlayerType typeX = get_player_type_choice("Player X", type_options);
    players[0] = create_player(nameX, 'X', typeX);

    string nameO = get_player_name("Player 2 (uses O)");
    PlayerType typeO = get_player_type_choice("Player O", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

Player<char>* XO_5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}
//=====================================================
// XO_5x5_GameManager Implementation
//=====================================================

XO_5x5_GameManager::XO_5x5_GameManager() {
    board = new XO_5x5_Board();
    ui = new XO_5x5_UI();
    players[0] = nullptr;
    players[1] = nullptr;
}

XO_5x5_GameManager::~XO_5x5_GameManager() {
    delete board;
    delete ui;
    delete players[0];
    delete players[1];
}

void XO_5x5_GameManager::run() {
    // Setup players
    Player<char>** playerArray = ui->setup_players();
    players[0] = playerArray[0];
    players[1] = playerArray[1];
    delete[] playerArray;

    // Set board pointers
    players[0]->set_board_ptr(board);
    players[1]->set_board_ptr(board);

    // Display initial board
    ui->display_board_matrix(board->get_board_matrix());

    // Main game loop - continue until 24 moves
    while (board->get_moves_count() < 24) {
        for (int i : {0, 1}) {
            Player<char>* currentPlayer = players[i];

            // Get and validate move
            Move<char>* move = ui->get_move(currentPlayer);
            while (!board->update_board(move)) {
                delete move;
                move = ui->get_move(currentPlayer);
            }
            delete move;

            // Display updated board
            ui->display_board_matrix(board->get_board_matrix());

            // Check if we reached 24 moves
            if (board->get_moves_count() >= 24) {
                break;
            }
        }
    }

    // Game over - determine winner
    board->display_scores(players[0], players[1]);

    if (board->is_win(players[0])) {
        ui->display_message(players[0]->get_name() + " wins!");
    }
    else if (board->is_win(players[1])) {
        ui->display_message(players[1]->get_name() + " wins!");
    }
    else {
        ui->display_message("It's a draw!");
    }
}