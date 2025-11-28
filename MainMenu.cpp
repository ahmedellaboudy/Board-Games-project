#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
#include "NumericalTicTacToe.h"
#include "XO_4x4_Classes.h"
#include "XO_5x5_Classes.h"
#include "MisereTicTacToe.h"
#include "infinity_XO.h"
#include "obstacles_6x6_tictactoe.h"

using namespace std;

void display_menu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "   BOARD GAMES COLLECTION - Part 1\n";
    cout << "========================================\n";
    cout << "1. Numerical Tic-Tac-Toe (Game 9)\n";
    cout << "2. 4x4 Tic-Tac-Toe (Game 7)\n";
    cout << "3. 5x5 Tic-Tac-Toe (Game 8)\n";
    cout << "4. Misere Tic-Tac-Toe\n";
    cout << "5. 6x6 Tic-Tac-Toe (Game 10) \n";
    cout << "6. infinty Tic-Tac-Toe (Game 11) \n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Choose a game or exit: ";
}

// -------------------- Game Functions --------------------
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
    cout << "\n=== Starting 5x5 Tic-Tac-Toe ===\n";
    XO_5x5_GameManager game_manager;
    game_manager.run();
    cout << "\n*** Game Ended ***\n";
}

void play_misere_tictactoe() {
    cout << "\n=== Starting Misere Tic-Tac-Toe ===\n";

    UI<char>* game_ui = new MisereTicTacToeUI();
    Board<char>* game_board = new MisereTicTacToe_board ();
    Player<char>** players = game_ui->setup_players();

    GameManager<char> game_manager(game_board, players, game_ui);
    game_manager.run();

    cout << "\n*** Game Ended ***\n";
}


void play_obstacles_6x6() {
    cout << "\n=== Starting 6x6 Tic-Tac-Toe ===\n";
    XO_6x6_GameManager game_manager;
    game_manager.run();
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
        cin >> choice;
        cin.ignore(1000, '\n');

        switch (choice) {
        case 1: play_numerical_tictactoe(); break;
        case 2: play_4x4_tictactoe(); break;
        case 3: play_5x5_tictactoe(); break;
        case 4: play_misere_tictactoe(); break;
        case 5: play_obstacles_6x6(); break;
        case 0:
            cout << "\nThank you for playing! Goodbye!\n";
            running = false;
            break;
        default:
            cout << "\nInvalid choice! Please select 0–5.\n";
            break;
        }
    }

    return 0;
}