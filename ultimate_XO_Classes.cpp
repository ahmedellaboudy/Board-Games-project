#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <memory>
#include "ultimate_XO_Classes.h"
#include "XO_Classes.h"

using namespace std;

//--------------------------------------- Ultimate_Tic_Tac_Toe_Board Implementation

Ultimate_XO_Board::Ultimate_XO_Board()
    : Board(3, 3), lastMoveBoardRow(-1), lastMoveBoardCol(-1) {

    // Initialize main board
    mainBoard = vector<vector<char>>(3, vector<char>(3, blank_symbol));

    // Initialize sub-boards
    subBoards.resize(3);
    for (int i = 0; i < 3; i++) {
        subBoards[i].resize(3);
        for (int j = 0; j < 3; j++) {
            subBoards[i][j] = new X_O_Board();
        }
    }
}

Ultimate_XO_Board::~Ultimate_XO_Board() {
    // Clean up sub-boards
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            delete subBoards[i][j];
        }
    }
}

bool Ultimate_XO_Board::update_board(Move<char>* move) {
    int boardRow, boardCol, cellRow, cellCol;

    // Decode the move coordinates
    // Assuming move->get_x() encodes boardRow * 3 + cellRow
    // and move->get_y() encodes boardCol * 3 + cellCol
    int encodedX = move->get_x();
    int encodedY = move->get_y();

    boardRow = encodedX / 3;
    cellRow = encodedX % 3;
    boardCol = encodedY / 3;
    cellCol = encodedY % 3;

    char mark = move->get_symbol();

    // Validate move
    if (boardRow < 0 || boardRow >= 3 || boardCol < 0 || boardCol >= 3 ||
        cellRow < 0 || cellRow >= 3 || cellCol < 0 || cellCol >= 3) {
        return false;
    }

    // Check if this board is available (not already won)
    if (mainBoard[boardRow][boardCol] != blank_symbol) {
        return false;
    }

    // Check if player must play in specific board (based on last move)
    if (lastMoveBoardRow != -1 && lastMoveBoardCol != -1) {
        if (lastMoveBoardRow != boardRow || lastMoveBoardCol != boardCol) {
            // Check if the required board is still playable
            if (mainBoard[lastMoveBoardRow][lastMoveBoardCol] == blank_symbol) {
                return false;  // Must play in the designated board
            }
        }
    }

    // Create a move for the sub-board
    Move<char> subMove(cellRow, cellCol, mark);

    // Update the sub-board
    bool success = subBoards[boardRow][boardCol]->update_board(&subMove);

    if (success) {
        // Update last move coordinates
        lastMoveBoardRow = cellRow;
        lastMoveBoardCol = cellCol;

        // Check if this sub-board is now won
        char winner = check_sub_board_win(boardRow, boardCol);
        if (winner != blank_symbol && winner != tie_symbol) {
            mainBoard[boardRow][boardCol] = winner;
        }

        n_moves++;
        return true;
    }

    return false;
}

char Ultimate_XO_Board::check_sub_board_win(int row, int col) {
    X_O_Board* board = subBoards[row][col];

    // Create temporary players for checking
    Player<char> xPlayer("X", 'X', PlayerType::HUMAN);
    Player<char> oPlayer("O", 'O', PlayerType::HUMAN);

    if (board->is_win(&xPlayer)) {
        return 'X';
    }
    else if (board->is_win(&oPlayer)) {
        return 'O';
    }
    else if (board->game_is_over(&xPlayer)) {  // Check for draw
        return tie_symbol;
    }

    return blank_symbol;
}

bool Ultimate_XO_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a == sym;
        };

    // Check rows and columns of main board
    for (int i = 0; i < 3; ++i) {
        if (all_equal(mainBoard[i][0], mainBoard[i][1], mainBoard[i][2]) ||
            all_equal(mainBoard[0][i], mainBoard[1][i], mainBoard[2][i])) {
            return true;
        }
    }

    // Check diagonals of main board
    if (all_equal(mainBoard[0][0], mainBoard[1][1], mainBoard[2][2]) ||
        all_equal(mainBoard[0][2], mainBoard[1][1], mainBoard[2][0])) {
        return true;
    }

    return false;
}

bool Ultimate_XO_Board::is_draw(Player<char>* player) {
    // Check if all main board cells are filled (with either X, O, or T)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (mainBoard[i][j] == blank_symbol) {
                return false;
            }
        }
    }

    // If all filled and no winner, it's a draw
    return !is_win(player);
}

bool Ultimate_XO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

vector<pair<int, int>> Ultimate_XO_Board::get_available_boards() {
    vector<pair<int, int>> available;

    if (lastMoveBoardRow == -1 || lastMoveBoardCol == -1) {
        // First move or board is won - player can choose any available board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (mainBoard[i][j] == blank_symbol) {
                    available.push_back({ i, j });
                }
            }
        }
    }
    else {
        // Player must play in the board corresponding to last move's cell
        if (mainBoard[lastMoveBoardRow][lastMoveBoardCol] == blank_symbol) {
            available.push_back({ lastMoveBoardRow, lastMoveBoardCol });
        }
        else {
            // If that board is won/tied, player can choose any available board
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (mainBoard[i][j] == blank_symbol) {
                        available.push_back({ i, j });
                    }
                }
            }
        }
    }

    return available;
}

void Ultimate_XO_Board::display_board() const {
    cout << "\nULTIMATE TIC TAC TOE BOARD:\n";
    cout << "============================\n\n";

    // Display column headers for main board
    cout << "     ";
    for (int mainCol = 0; mainCol < 3; mainCol++) {
        cout << " Board " << mainCol << "       ";
    }
    cout << "\n";

    for (int mainRow = 0; mainRow < 3; mainRow++) {
        // Display 3 rows of each sub-board
        for (int subRow = 0; subRow < 3; subRow++) {
            if (subRow == 1) {
                cout << "B" << mainRow << " ";
            }
            else {
                cout << "   ";
            }

            for (int mainCol = 0; mainCol < 3; mainCol++) {
                // Display one row of the sub-board
                cout << " ";
                for (int subCol = 0; subCol < 3; subCol++) {
                    // Get the cell from sub-board
                    vector<vector<char>> subBoardState = subBoards[mainRow][mainCol]->display_board();
                    char cell = subBoardState[subRow][subCol];

                    // If sub-board is won, show the winner
                    if (mainBoard[mainRow][mainCol] != blank_symbol && subRow == 1 && subCol == 1) {
                        cout << " " << mainBoard[mainRow][mainCol] << " ";
                    }
                    else {
                        cout << " " << cell << " ";
                    }

                    if (subCol < 2) cout << "|";
                }
                cout << "  ";
            }
            cout << "\n";

            if (subRow < 2) {
                cout << "     ";
                for (int mainCol = 0; mainCol < 3; mainCol++) {
                    cout << "---+---+---  ";
                }
                cout << "\n";
            }
        }

        if (mainRow < 2) {
            cout << "     ";
            for (int mainCol = 0; mainCol < 3; mainCol++) {
                cout << "           =====";
            }
            cout << "\n";
        }
    }

    // Display main board status
    cout << "\nMAIN BOARD STATUS:\n";
    cout << "===============\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << " " << mainBoard[i][j] << " ";
            if (j < 2) cout << "|";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

//--------------------------------------- Ultimate_Tic_Tac_Toe_UI Implementation

Ultimate_XO_UI::Ultimate_XO_UI():ValidatedUI<char>("Welcome to FCAI Ultimate Tic Tac Toe Game", 3) {}

Player<char>* Ultimate_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Ultimate_XO_UI::get_move(Player<char>* player) {
    int boardRow, boardCol, cellRow, cellCol;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";

        // Get available boards
        Ultimate_XO_Board* board =
            dynamic_cast<Ultimate_XO_Board*>(player->get_board_ptr());

        if (!board) {
            cerr << "Error: Board is not Ultimate_Tic_Tac_Toe_Board!\n";
            return nullptr;
        }

        vector<pair<int, int>> availableBoards = board->get_available_boards();

        cout << "Available boards to play in: ";
        for (auto& b : availableBoards) {
            cout << "(" << b.first << "," << b.second << ") ";
        }
        cout << "\n";

        cout << "Enter board row and column (0-2): ";
        cin >> boardRow >> boardCol;

        cout << "Enter cell row and column within board (0-2): ";
        cin >> cellRow >> cellCol;

        // Encode coordinates: boardRow*3 + cellRow, boardCol*3 + cellCol
        int encodedX = boardRow * 3 + cellRow;
        int encodedY = boardCol * 3 + cellCol;

        return new Move<char>(encodedX, encodedY, player->get_symbol());
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Simple AI: choose random available board and random cell within it
        Ultimate_XO_Board* board =
            dynamic_cast<Ultimate_XO_Board*>(player->get_board_ptr());

        if (!board) {
            cerr << "Error: Board is not Ultimate_Tic_Tac_Toe_Board!\n";
            return nullptr;
        }

        vector<pair<int, int>> availableBoards = board->get_available_boards();

        if (availableBoards.empty()) {
            return nullptr;
        }

        // Choose random available board
        int boardIndex = rand() % availableBoards.size();
        boardRow = availableBoards[boardIndex].first;
        boardCol = availableBoards[boardIndex].second;

        // Choose random cell within that board
        cellRow = rand() % 3;
        cellCol = rand() % 3;

        cout << "Computer chooses board (" << boardRow << "," << boardCol
            << "), cell (" << cellRow << "," << cellCol << ")\n";

        int encodedX = boardRow * 3 + cellRow;
        int encodedY = boardCol * 3 + cellCol;

        return new Move<char>(encodedX, encodedY, player->get_symbol());
    }

    return nullptr;
}