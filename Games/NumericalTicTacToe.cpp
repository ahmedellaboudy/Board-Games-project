#include "NumericalTicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Numerical_Board::Numerical_Board() : Board(3, 3) {

    for (auto& row : board) {
        for (auto& cell : row) {
            cell = blank_value;
        }
    }
}

bool Numerical_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int number = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position! Row and column must be between 0 and 2.\n";
        return false;
    }

    if (board[x][y] != blank_value) {
        cout << "Cell already occupied!\n";
        return false;
    }

    if (used_numbers.count(number)) {
        cout << "Number " << number << " has already been used!\n";
        return false;
    }

    board[x][y] = number;
    used_numbers.insert(number);
    n_moves++;
    
    return true;
}

bool Numerical_Board::is_win(Player<int>* player) {

    for (int i = 0; i < rows; ++i) {
        if (board[i][0] != blank_value && 
            board[i][1] != blank_value && 
            board[i][2] != blank_value) {
            if (board[i][0] + board[i][1] + board[i][2] == 15) {
                return true;
            }
        }
    }

    for (int j = 0; j < columns; ++j) {
        if (board[0][j] != blank_value && 
            board[1][j] != blank_value && 
            board[2][j] != blank_value) {
            if (board[0][j] + board[1][j] + board[2][j] == 15) {
                return true;
            }
        }
    }

    if (board[0][0] != blank_value && 
        board[1][1] != blank_value && 
        board[2][2] != blank_value) {
        if (board[0][0] + board[1][1] + board[2][2] == 15) {
            return true;
        }
    }

    if (board[0][2] != blank_value && 
        board[1][1] != blank_value && 
        board[2][0] != blank_value) {
        if (board[0][2] + board[1][1] + board[2][0] == 15) {
            return true;
        }
    }

    return false;
}

bool Numerical_Board::is_draw(Player<int>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Numerical_Board::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}

bool Numerical_Board::is_number_used(int number) const {
    return used_numbers.count(number) > 0;
}


Numerical_Player::Numerical_Player(string name, int player_number) 
    : Player<int>(name, player_number, PlayerType::HUMAN) {
    
    if (player_number == 1) {

        available_numbers = {1, 3, 5, 7, 9};
    } else {

        available_numbers = {2, 4, 6, 8};
    }
}

void Numerical_Player::use_number(int number) {
    available_numbers.erase(number);
}


Numerical_Random_Player::Numerical_Random_Player(int player_number)
    : Numerical_Player("Computer Player " + to_string(player_number), player_number) {
    type = PlayerType::COMPUTER;
}


Numerical_UI::Numerical_UI() 
    : ValidatedUI<int>("Welcome to Numerical Tic-Tac-Toe!\n"
              "Player 1 uses odd numbers (1,3,5,7,9)\n"
              "Player 2 uses even numbers (2,4,6,8)\n"
              "Goal: Make three numbers sum to 15 in a row!", 3) {}

Move<int>* Numerical_UI::get_move(Player<int>* player) {
    int x, y, number;

    Numerical_Player* num_player = dynamic_cast<Numerical_Player*>(player);

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn\n";
        cout << "Available numbers: ";
        for (int num : num_player->get_available_numbers()) {
            cout << num << " ";
        }
        cout << "\n";

        // Get position with validation (0-2 range)
        auto pos = get_validated_position(
            "Enter row (0-2) and column (0-2): ",
            3,  // 0-2 range
            3,
            player->get_board_ptr(),
            0  // empty symbol for int board
        );
        x = pos.first;
        y = pos.second;

        // Validate number
        while (true) {
            cout << "Enter number: ";
            if (cin >> number) {
                if (num_player->get_available_numbers().count(number) > 0) {
                    break;
                }
                cout << "Invalid number! Choose from your available numbers.\n";
            } else {
                cout << "Invalid input! Please enter a number.\n";
                clear_input_buffer();
            }
        }

    } else if (player->get_type() == PlayerType::COMPUTER) {
        Numerical_Board* board = dynamic_cast<Numerical_Board*>(player->get_board_ptr());

        vector<pair<int, int>> empty_positions;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                auto board_matrix = board->get_board_matrix();
                if (board_matrix[i][j] == 0) {
                    empty_positions.push_back({i, j});
                }
            }
        }

        int pos_idx = rand() % empty_positions.size();
        x = empty_positions[pos_idx].first;
        y = empty_positions[pos_idx].second;

        auto& available = num_player->get_available_numbers();
        auto it = available.begin();
        advance(it, rand() % available.size());
        number = *it;

        cout << "\n" << player->get_name() << " plays: "
             << number << " at position (" << x << ", " << y << ")\n";
    }

    num_player->use_number(number);
    return new Move<int>(x, y, number);
}

Player<int>* Numerical_UI::create_player(string& name, int symbol, PlayerType type) {
    if (type == PlayerType::HUMAN) {
        return new Numerical_Player(name, symbol);
    } else {
        return new Numerical_Random_Player(symbol);
    }
}

Player<int>** Numerical_UI::setup_players() {
    Player<int>** players = new Player<int>*[2];
    vector<string> type_options = {"Human", "Computer"};

    cout << "\n=== Player 1 Setup (Odd Numbers: 1,3,5,7,9) ===\n";
    string name1 = get_player_name("Player 1");
    PlayerType type1 = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(name1, 1, type1);

    cout << "\n=== Player 2 Setup (Even Numbers: 2,4,6,8) ===\n";
    string name2 = get_player_name("Player 2");
    PlayerType type2 = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(name2, 2, type2);

    return players;
}
