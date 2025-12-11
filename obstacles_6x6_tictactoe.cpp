#include "obstacles_6x6_tictactoe.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

// -----------------------------------------------------
// XO_6x6_Board Implementation
// -----------------------------------------------------

XO_6x6_Board::XO_6x6_Board() : Board(6, 6), obstacles_count(0) {
    // Initialize empty board
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            board[i][j] = ' ';
        }
    }

    //// >>> CHANGE: No obstacles at start
    // add_random_obstacles();
    //// <<< CHANGE
}

void XO_6x6_Board::add_random_obstacles() {
    int count = 0;
    while (count < 2) {
        int x = rand() % 6;
        int y = rand() % 6;

        if (board[x][y] == ' ') {
            board[x][y] = '#';
            count++;
            obstacles_count++;
        }
    }
}

bool XO_6x6_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Check if move is valid
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position! Please choose between (0-5, 0-5)\n";
        return false;
    }

    if (board[x][y] != ' ') {
        cout << "Cell is already occupied! Choose another cell.\n";
        return false;
    }

    // Update board
    board[x][y] = symbol;
    n_moves++;

    //// >>> CHANGE: Add obstacles only after both X and O have played
    if (n_moves >= 2 && n_moves % 2 == 0) {
        add_random_obstacles();
    }
    //// <<< CHANGE

    return true;
}

bool XO_6x6_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();
    return check_four_in_row(sym);
}

bool XO_6x6_Board::is_draw(Player<char>* player) {
    return (n_moves == 36 - obstacles_count && !is_win(player));
}

bool XO_6x6_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void XO_6x6_Board::display_scores(Player<char>* player1, Player<char>* player2) {
    int score1 = 0, score2 = 0;

    char sym1 = player1->get_symbol();
    char sym2 = player2->get_symbol();

    if (check_four_in_row(sym1)) score1++;
    if (check_four_in_row(sym2)) score2++;

    cout << "\n========== SCORES ==========\n";
    cout << player1->get_name() << " (" << sym1 << "): " << score1 << " wins\n";
    cout << player2->get_name() << " (" << sym2 << "): " << score2 << " wins\n";
    cout << "============================\n\n";
}

int XO_6x6_Board::get_obstacles_count() {
    return obstacles_count;
}

// -----------------------------------------------------
// XO_6x6_UI Implementation
// -----------------------------------------------------

XO_6x6_UI::XO_6x6_UI() : ValidatedUI<char>("Welcome to 6x6 Tic-Tac-Toe with Obstacles!", 3) {
    cout << "Game rule: connect 4 (row or column or diagonal) with no obstacles\n";
}

XO_6x6_UI::~XO_6x6_UI() {}

Player<char>* XO_6x6_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}
Move<char>* XO_6x6_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        auto pos = get_validated_position(
            "\n" + player->get_name() + ", enter your move x and y (0 to 5): ",
            6,
            6,
            player->get_board_ptr(),
            ' '
        );
        x = pos.first;
        y = pos.second;
    } else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }

    return new Move<char>(x, y, player->get_symbol());
}

// -----------------------------------------------------
// XO_6x6_GameManager Implementation
// -----------------------------------------------------

XO_6x6_GameManager::XO_6x6_GameManager() {
    board = new XO_6x6_Board();
    ui = new XO_6x6_UI();
    players[0] = nullptr;
    players[1] = nullptr;
}

XO_6x6_GameManager::~XO_6x6_GameManager() {
    delete board;
    delete ui;
    if (players[0]) delete players[0];
    if (players[1]) delete players[1];
}

void XO_6x6_GameManager::run() {
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

    // Calculate max moves dynamically
    int max_moves = board->get_rows() * board->get_columns() - board->get_obstacles_count();

    //// >>> CHANGE: Added turn count to track when to start obstacles
    int turnCount = 0;
    //// <<< CHANGE

    // Main game loop
    while (board->get_moves_count() < max_moves) {
        for (int i : {0, 1}) {
            Player<char>* currentPlayer = players[i];

            // Get and validate move
            Move<char>* move = ui->get_move(currentPlayer);
            while (!board->update_board(move)) {
                delete move;
                move = ui->get_move(currentPlayer);
            }
            delete move;

            //// >>> CHANGE: Increment turn count
            turnCount++;
            //// <<< CHANGE

            // Display updated board
            ui->display_board_matrix(board->get_board_matrix());

            // Check for win
            if (board->is_win(currentPlayer)) {
                ui->display_message(currentPlayer->get_name() + " wins!");
                return;
            }

            // Check if reached max moves
            if (board->get_moves_count() >= max_moves) {
                break;
            }
        }
    }

    // Display final scores
    board->display_scores(players[0], players[1]);

    // Check for winner
    if (board->is_win(players[0])) {
        ui->display_message(players[0]->get_name() + " wins!");
    } else if (board->is_win(players[1])) {
        ui->display_message(players[1]->get_name() + " wins!");
    } else {
        ui->display_message("It's a draw!");
    }
}