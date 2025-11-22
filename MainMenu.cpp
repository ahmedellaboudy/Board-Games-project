/**
 * @file MainMenu.cpp
 * @brief Main menu for Board Games Application
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
#include "NumericalTicTacToe.h"

using namespace std;

void display_menu() {
    cout << "\n";
    cout << "========================================\n";
    cout << "   BOARD GAMES COLLECTION - Part 1\n";
    cout << "========================================\n";
    cout << "1. Numerical Tic-Tac-Toe (Game 9)\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Choose a game or to exit: ";
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
            case 1:
                play_numerical_tictactoe();
                break;

            case 0:
                cout << "\nThank you for playing! Goodbye!\n";
                running = false;
                break;

            default:
                cout << "\nInvalid choice! Please select 1 or 0.\n";
                break;
        }
    }

    return 0;
}