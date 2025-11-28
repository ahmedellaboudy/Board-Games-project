#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "BoardGame_Classes.h"
#include "NumericalTicTacToe.h"
#include "XO_4x4_Classes.h"
#include "XO_5x5_Classes.h"
#include "MisereTicTacToe.h"
#include "obstacles_6x6_tictactoe.h"
#include "infinity_XO.h"
#include "sus.h"

using namespace std;

void display_menu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "        BOARD GAMES COLLECTION \n";
    cout << "========================================\n";
    cout << "1. SUS Game\n";
    cout << "2. 5x5 Tic-Tac-Toe\n";
    cout << "3. Misere Tic-Tac-Toe\n";
    cout << "4. 4x4 Tic-Tac-Toe \n";
    cout << "5. Numerical Tic-Tac-Toe \n";
    cout << "6. Obstacles 6x6 Tic-Tac-Toe\n";
    cout << "7. Infinity XO Tic-Tac-Toe\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Choose a game or exit: ";
}

// -------------------- Game Functions --------------------

void play_sus_game() {
    cout << "\n=== Starting SUS Game ===\n";
    UI<char>* game_ui = new SUS_UI();
    Board<char>* game_board = new SUS_Board();

    Player<char>** players = new Player<char>*[2];

    cout << "\n=== Player Setup ===\n";
    string name1, name2;
    cout << "Enter Player 1 name (will use 'S'): ";
    getline(cin >> ws, name1);

    cout << "Choose Player 1 type:\n1. Human\n2. Computer\n";
    int choice1;
    while (!(cin >> choice1) || (choice1 != 1 && choice1 != 2)) {
        cout << "Invalid choice! Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    PlayerType type1 = (choice1 == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;

    cout << "\nEnter Player 2 name (will use 'U'): ";
    getline(cin >> ws, name2);

    cout << "Choose Player 2 type:\n1. Human\n2. Computer\n";
    int choice2;
    while (!(cin >> choice2) || (choice2 != 1 && choice2 != 2)) {
        cout << "Invalid choice! Enter 1 or 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    PlayerType type2 = (choice2 == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;

    players[0] = game_ui->create_player(name1, 'S', type1);
    players[1] = game_ui->create_player(name2, 'U', type2);

    players[0]->set_board_ptr(game_board);
    players[1]->set_board_ptr(game_board);

    game_ui->display_board_matrix(game_board->get_board_matrix());

    Player<char>* currentPlayer = players[0];
    while (!game_board->game_is_over(currentPlayer)) {
        for (int i : {0, 1}) {
            currentPlayer = players[i];
            Move<char>* move = game_ui->get_move(currentPlayer);

            while (!game_board->update_board(move)) {
                cout << "Invalid move! Try again.\n";
                delete move;
                move = game_ui->get_move(currentPlayer);
            }

            delete move;
            game_ui->display_board_matrix(game_board->get_board_matrix());

            if (game_board->game_is_over(currentPlayer)) {
                break;
            }
        }
    }

    auto scores = dynamic_cast<SUS_Board*>(game_board)->get_scores();
    dynamic_cast<SUS_UI*>(game_ui)->display_scores(scores.first, scores.second);

    if (scores.first > scores.second) {
        game_ui->display_message(players[0]->get_name() + " wins with " +
                                to_string(scores.first) + " S-U-S sequences!");
    } else if (scores.second > scores.first) {
        game_ui->display_message(players[1]->get_name() + " wins with " +
                                to_string(scores.second) + " S-U-S sequences!");
    } else {
        game_ui->display_message("It's a draw! Both players have " +
                                to_string(scores.first) + " S-U-S sequences!");
    }

    delete game_board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete game_ui;

    cout << "\n*** Game Ended ***\n";
}

void play_numerical_tictactoe() {
    cout << "\n=== Starting Numerical Tic-Tac-Toe ===\n";
    UI<int>* game_ui = new Numerical_UI();
    Board<int>* game_board = new Numerical_Board();
    Player<int>** players = game_ui->setup_players();

    GameManager<int> game_manager(game_board, players, game_ui);
    game_manager.run();

    delete game_board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete game_ui;

    cout << "\n*** Game Ended ***\n";
}

void play_4x4_tictactoe() {
    cout << "\n=== Starting 4x4 Tic-Tac-Toe ===\n";
    UI<char>* game_ui = new XO_4x4_UI();
    Board<char>* game_board = new XO_4x4_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game_manager(game_board, players, game_ui);
    game_manager.run();

    delete game_board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete game_ui;

    cout << "\n*** Game Ended ***\n";
}

void play_5x5_tictactoe() {
    cout << "\n=== Starting 5x5 Three-in-a-Row ===\n";
    XO_5x5_GameManager game_manager;
    game_manager.run();
    cout << "\n*** Game Ended ***\n";
}

void play_misere_tictactoe() {
    cout << "\n=== Starting Misere Tic-Tac-Toe ===\n";
    UI<char>* game_ui = new Misere_UI();
    Board<char>* game_board = new Misere_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game_manager(game_board, players, game_ui);
    game_manager.run();

    delete game_board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete game_ui;

    cout << "\n*** Game Ended ***\n";
}

void play_6x6_tictactoe() {
    cout << "\n=== Starting 6x6 Obstacle Four-in-a-Row ===\n";
    XO_6x6_GameManager game_manager;
    game_manager.run();
    cout << "\n*** Game Ended ***\n";
}

void play_infinity_XO() {
    cout << "\n=== Starting 3x3 Infinity XO Tic-Tac-Toe ===\n";
    UI<char>* game_ui = new infinity_UI();
    Board<char>* game_board = new infinity_Board();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game_manager(game_board, players, game_ui);
    game_manager.run();

    delete game_board;
    delete players[0];
    delete players[1];
    delete[] players;
    delete game_ui;

    cout << "\n*** Game Ended ***\n";
}

// -------------------- Main --------------------
int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice;
    bool running = true;

    cout << "Welcome to the Board Games Application!\n";

    while (running) {
        display_menu();

        // Input validation
        if (!(cin >> choice)) {
            cout << "\nInvalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1: play_sus_game(); break;
        case 2: play_5x5_tictactoe(); break;
        case 3: play_misere_tictactoe(); break;
        case 4: play_4x4_tictactoe(); break;
        case 5: play_numerical_tictactoe(); break;
        case 6: play_6x6_tictactoe(); break;
        case 7: play_infinity_XO(); break;
        case 0:
            cout << "\nThank you for playing! Goodbye!\n";
            running = false;
            break;
        default:
            cout << "\nInvalid choice! Please select 0-7.\n";
            break;
        }
    }

    return 0;
}