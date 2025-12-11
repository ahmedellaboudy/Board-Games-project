#include "ultimate_XO_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// ============ Ultimate_XO_Board Implementation ============

Ultimate_XO_Board::Ultimate_XO_Board() 
    : Board(3, 3) {

    // Initialize main board (tracks which sub-boards are won)
    mainBoard = vector<vector<char>>(3, vector<char>(3, ' '));

    // Create 9 sub-boards
    subBoards.resize(3);
    for (int i = 0; i < 3; i++) {
        subBoards[i].resize(3);
        for (int j = 0; j < 3; j++) {
            subBoards[i][j] = new X_O_Board();
        }
    }
}

Ultimate_XO_Board::~Ultimate_XO_Board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            delete subBoards[i][j];
        }
    }
}

bool Ultimate_XO_Board::update_board(Move<char>* move) {
    int boardRow = move->get_x();
    int boardCol = move->get_y();

    // Decode: x = boardRow*10 + cellRow, y = boardCol*10 + cellCol
    int cellRow = boardRow % 10;
    boardRow = boardRow / 10;
    int cellCol = boardCol % 10;
    boardCol = boardCol / 10;

    // Validate coordinates
    if (boardRow < 0 || boardRow > 2 || boardCol < 0 || boardCol > 2 ||
        cellRow < 0 || cellRow > 2 || cellCol < 0 || cellCol > 2) {
        cout << "Invalid move coordinates!\n";
        return false;
    }

    // Check if this sub-board is already won
    if (mainBoard[boardRow][boardCol] != ' ') {
        cout << "This board has already been won!\n";
        return false;
    }

    // Try to make move in sub-board
    Move<char> subMove(cellRow, cellCol, move->get_symbol());
    if (!subBoards[boardRow][boardCol]->update_board(&subMove)) {
        return false;
    }

    // Update successful
    n_moves++;

    // Check if this sub-board is now won
    char winner = check_sub_board_winner(boardRow, boardCol);
    if (winner != ' ') {
        mainBoard[boardRow][boardCol] = winner;
    }

    return true;
}

char Ultimate_XO_Board::check_sub_board_winner(int boardRow, int boardCol) {
    X_O_Board* board = subBoards[boardRow][boardCol];

    // Create dummy players to check win conditions
    Player<char> xPlayer("X", 'X', PlayerType::HUMAN);
    Player<char> oPlayer("O", 'O', PlayerType::HUMAN);
    xPlayer.set_board_ptr(board);
    oPlayer.set_board_ptr(board);

    if (board->is_win(&xPlayer)) {
        return 'X';
    }
    if (board->is_win(&oPlayer)) {
        return 'O';
    }
    if (board->is_draw(&xPlayer)) {
        return 'T';  // Tie
    }

    return ' ';  // Still playing
}

bool Ultimate_XO_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    // Check rows
    for (int i = 0; i < 3; i++) {
        if (mainBoard[i][0] == sym && mainBoard[i][1] == sym && mainBoard[i][2] == sym) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (mainBoard[0][j] == sym && mainBoard[1][j] == sym && mainBoard[2][j] == sym) {
            return true;
        }
    }

    // Check diagonals
    if (mainBoard[0][0] == sym && mainBoard[1][1] == sym && mainBoard[2][2] == sym) {
        return true;
    }
    if (mainBoard[0][2] == sym && mainBoard[1][1] == sym && mainBoard[2][0] == sym) {
        return true;
    }

    return false;
}

bool Ultimate_XO_Board::is_draw(Player<char>* player) {
    // Check if all sub-boards are complete
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (mainBoard[i][j] == ' ') {
                return false;  // Still have available boards
            }
        }
    }

    // All boards complete - check if anyone won
    Player<char> xPlayer("X", 'X', PlayerType::HUMAN);
    Player<char> oPlayer("O", 'O', PlayerType::HUMAN);

    return !is_win(&xPlayer) && !is_win(&oPlayer);
}

bool Ultimate_XO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

bool Ultimate_XO_Board::is_board_available(int boardRow, int boardCol) {
    if (boardRow < 0 || boardRow > 2 || boardCol < 0 || boardCol > 2) {
        return false;
    }
    return mainBoard[boardRow][boardCol] == ' ';
}

X_O_Board* Ultimate_XO_Board::get_sub_board(int row, int col) const {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return subBoards[row][col];
    }
    return nullptr;
}

// ============ Ultimate_XO_UI Implementation ============

Ultimate_XO_UI::Ultimate_XO_UI()
    : ValidatedUI<char>("=== Ultimate Tic Tac Toe ===\n"
                        "Win 3 sub-boards in a row to win the game!", 3) {
}

Player<char>* Ultimate_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* Ultimate_XO_UI::get_move(Player<char>* player) {
    Ultimate_XO_Board* board = dynamic_cast<Ultimate_XO_Board*>(player->get_board_ptr());

    if (!board) {
        cerr << "Error: Invalid board type!\n";
        return nullptr;
    }

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "'s turn (" << player->get_symbol() << ")\n";
        cout << "Choose any available board to play in.\n";

        // Use validated input from ValidatedUI
        pair<int, int> boardPos = get_validated_position(
            "Enter board position (row col, 0-2): ", 3, 3);
        int boardRow = boardPos.first;
        int boardCol = boardPos.second;

        // Get cell position with validation
        pair<int, int> cellPos = get_validated_position(
            "Enter cell position in that board (row col, 0-2): ", 3, 3);
        int cellRow = cellPos.first;
        int cellCol = cellPos.second;

        // Encode as boardRow*10 + cellRow and boardCol*10 + cellCol
        int encodedX = boardRow * 10 + cellRow;
        int encodedY = boardCol * 10 + cellCol;

        return new Move<char>(encodedX, encodedY, player->get_symbol());
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Random computer player - pick any available board
        vector<pair<int,int>> availableBoards;

        // Find all available boards
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board->is_board_available(i, j)) {
                    availableBoards.push_back({i, j});
                }
            }
        }

        if (availableBoards.empty()) {
            cout << "No available boards for computer!\n";
            return nullptr;
        }

        // Pick random board
        int boardIdx = rand() % availableBoards.size();
        int boardRow = availableBoards[boardIdx].first;
        int boardCol = availableBoards[boardIdx].second;

        // Pick random empty cell in that board
        X_O_Board* subBoard = board->get_sub_board(boardRow, boardCol);
        if (!subBoard) {
            cout << "Invalid sub-board!\n";
            return nullptr;
        }

        // Get the board matrix to check empty cells
        auto subMatrix = subBoard->get_board_matrix();
        vector<pair<int,int>> emptyCells;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // X_O_Board uses '.' for empty cells, not ' '
                if (subMatrix[i][j] == ' ' || subMatrix[i][j] == '.') {
                    emptyCells.push_back({i, j});
                }
            }
        }

        if (emptyCells.empty()) {
            cout << "No empty cells in selected board!\n";
            return nullptr;
        }

        int cellIdx = rand() % emptyCells.size();
        int cellRow = emptyCells[cellIdx].first;
        int cellCol = emptyCells[cellIdx].second;

        cout << "\nComputer plays: Board(" << boardRow << "," << boardCol
             << ") Cell(" << cellRow << "," << cellCol << ")\n";

        int encodedX = boardRow * 10 + cellRow;
        int encodedY = boardCol * 10 + cellCol;

        return new Move<char>(encodedX, encodedY, player->get_symbol());
    }

    return nullptr;
}

void Ultimate_XO_UI::display_board_matrix(const vector<vector<char>>& matrix) const {
    // This will be called by GameManager - we need to cast and call our custom display
    // For now, just show a message
    cout << "\n(Board updated - see full display above)\n";
}

void Ultimate_XO_UI::display_full_board(Ultimate_XO_Board* board) const {
    cout << "\n=== MAIN BOARD STATUS ===\n";
    display_main_board(board);

    cout << "\n=== ALL SUB-BOARDS ===\n";
    cout << "Format: Board(row,col) where 0,0 is top-left\n\n";

    // Display all 9 sub-boards in a 3x3 layout
    for (int boardRow = 0; boardRow < 3; boardRow++) {
        // For each row of boards
        cout << "  Board Row " << boardRow << ":\n";

        for (int subRow = 0; subRow < 3; subRow++) {
            // For each row within the sub-boards
            cout << "  ";  // Indent

            for (int boardCol = 0; boardCol < 3; boardCol++) {
                X_O_Board* subBoard = board->get_sub_board(boardRow, boardCol);
                auto subMatrix = subBoard->get_board_matrix();

                if (boardCol > 0) cout << "    ";  // Space between boards

                for (int subCol = 0; subCol < 3; subCol++) {
                    char cell = subMatrix[subRow][subCol];
                    cout << " " << cell;
                    if (subCol < 2) cout << " |";
                }
            }
            cout << "\n";

            if (subRow < 2) {
                cout << "  ";
                for (int boardCol = 0; boardCol < 3; boardCol++) {
                    if (boardCol > 0) cout << "    ";
                    cout << "-----------";
                }
                cout << "\n";
            }
        }
        
        if (boardRow < 2) {
            cout << "\n";
        }
    }
    cout << "\n";
}

void Ultimate_XO_UI::display_main_board(Ultimate_XO_Board* board) const {
    auto mainBoard = board->get_main_board();
    
    cout << "   0   1   2\n";
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++) {
            cout << " " << mainBoard[i][j] << " ";
            if (j < 2) cout << "|";
        }
        cout << "\n";
        if (i < 2) {
            cout << "  -----------\n";
        }
    }
}
