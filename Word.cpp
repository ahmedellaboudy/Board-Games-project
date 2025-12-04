#include "word.h"

//-----------------------------------------------------
// WordBoard Implementation
//-----------------------------------------------------

WordBoard::WordBoard(const string& dict_file) : Board<char>(3, 3) {
    // Initialize board with empty spaces
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    load_dictionary(dict_file);
}

void WordBoard::load_dictionary(const string& filename) {
    ifstream file("dic.txt");
    if (!file.is_open()) {
        cerr << "ERROR: Could not open dictionary file '" << filename << "'\n";
        cerr << "Please make sure 'dic.txt' exists in the same directory.\n";
        exit(1);
    }

    string word;
    while (file >> word) {
        // Convert to uppercase and store
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() == 3) {
            dictionary.insert(word);
        }
    }
    file.close();

    if (dictionary.empty()) {
        cerr << "ERROR: No words loaded from dictionary!\n";
        exit(1);
    }

    cout << "✓ Loaded " << dictionary.size() << " words from dictionary.\n";
}

bool WordBoard::is_valid_word(const string& word) const {
    if (word.length() != 3) return false;

    // Check if word contains only letters (no spaces)
    for (char c : word) {
        if (c == ' ') return false;
    }

    return dictionary.find(word) != dictionary.end();
}

string WordBoard::extract_word(int row, int col, int dr, int dc) const {
    string word = "";
    for (int i = 0; i < 3; i++) {
        int r = row + i * dr;
        int c = col + i * dc;
        if (r < 0 || r >= 3 || c < 0 || c >= 3) return "";
        word += board[r][c];
    }
    return word;
}

bool WordBoard::has_valid_word() const {
    // Check all rows
    for (int i = 0; i < 3; i++) {
        string word = extract_word(i, 0, 0, 1);
        if (is_valid_word(word)) {
            cout << "Valid word found: " << word << " (Row " << i << ")\n";
            return true;
        }
    }

    // Check all columns
    for (int j = 0; j < 3; j++) {
        string word = extract_word(0, j, 1, 0);
        if (is_valid_word(word)) {
            cout << "Valid word found: " << word << " (Column " << j << ")\n";
            return true;
        }
    }

    // Check diagonal (top-left to bottom-right)
    string diag1 = extract_word(0, 0, 1, 1);
    if (is_valid_word(diag1)) {
        cout << "Valid word found: " << diag1 << " (Diagonal \\)\n";
        return true;
    }

    // Check diagonal (top-right to bottom-left)
    string diag2 = extract_word(0, 2, 1, -1);
    if (is_valid_word(diag2)) {
        cout << "Valid word found: " << diag2 << " (Diagonal /)\n";
        return true;
    }

    return false;
}

bool WordBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char letter = move->get_symbol();

    // Validate position
    if (x < 0 || x >= 3 || y < 0 || y >= 3) {
        cout << "Invalid position! Row and column must be between 0 and 2.\n";
        return false;
    }

    // Check if cell is empty
    if (board[x][y] != ' ') {
        cout << "Cell is already occupied!\n";
        return false;
    }

    // Validate letter input
    if (!isalpha(letter)) {
        cout << "Invalid input! Please enter a letter.\n";
        return false;
    }

    // Place the letter on the board
    board[x][y] = toupper(letter);
    n_moves++;

    // Debug: Check for words after each move
    cout << "\n[Checking for words...]\n";

    // Check row
    string row_word = extract_word(x, 0, 0, 1);
    cout << "Row " << x << ": " << row_word;
    if (row_word.find(' ') == string::npos) {
        cout << " -> " << (is_valid_word(row_word) ? "VALID!" : "Invalid");
    }
    cout << "\n";

    // Check column
    string col_word = extract_word(0, y, 1, 0);
    cout << "Col " << y << ": " << col_word;
    if (col_word.find(' ') == string::npos) {
        cout << " -> " << (is_valid_word(col_word) ? "VALID!" : "Invalid");
    }
    cout << "\n";

    // Check diagonals if applicable
    if (x == y) {
        string diag1 = extract_word(0, 0, 1, 1);
        cout << "Diag \\: " << diag1;
        if (diag1.find(' ') == string::npos) {
            cout << " -> " << (is_valid_word(diag1) ? "VALID!" : "Invalid");
        }
        cout << "\n";
    }

    if (x + y == 2) {
        string diag2 = extract_word(0, 2, 1, -1);
        cout << "Diag /: " << diag2;
        if (diag2.find(' ') == string::npos) {
            cout << " -> " << (is_valid_word(diag2) ? "VALID!" : "Invalid");
        }
        cout << "\n";
    }

    return true;
}

bool WordBoard::is_win(Player<char>* player) {
    return has_valid_word();
}

bool WordBoard::is_lose(Player<char>* player) {
    return false; // Not applicable in this game
}

bool WordBoard::is_draw(Player<char>* player) {
    // Draw if board is full and no valid word exists
    return n_moves == 9 && !has_valid_word();
}

bool WordBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//-----------------------------------------------------
// WordPlayer Implementation
//-----------------------------------------------------

WordPlayer::WordPlayer(string name, char symbol)
    : Player<char>(name, symbol, PlayerType::HUMAN) {}

//-----------------------------------------------------
// WordComputerPlayer Implementation
//-----------------------------------------------------

WordComputerPlayer::WordComputerPlayer(char symbol)
    : Player<char>("Computer", symbol, PlayerType::COMPUTER) {}

//-----------------------------------------------------
// WordUI Implementation
//-----------------------------------------------------



WordUI::WordUI()
    : UI<char>("Welcome to Word Tic-Tac-Toe!\n"
        "Form a valid 3-letter word horizontally, vertically, or diagonally to win!", 3) {
}

Move<char>* WordUI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::COMPUTER) {
        // Simple random AI
        vector<vector<char>> board_matrix = player->get_board_ptr()->get_board_matrix();
        vector<pair<int, int>> empty_cells;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board_matrix[i][j] == ' ') {
                    empty_cells.push_back({ i, j });
                }
            }
        }

        if (empty_cells.empty()) {
            return new Move<char>(0, 0, 'A');
        }

        // Pick random empty cell
        int idx = rand() % empty_cells.size();
        int x = empty_cells[idx].first;
        int y = empty_cells[idx].second;

        // Pick random letter
        char letter = 'A' + (rand() % 26);

        cout << "Computer plays: " << letter << " at position (" << x << ", " << y << ")\n";
        return new Move<char>(x, y, letter);
    }

    // Human player
    cout << player->get_name() << "'s turn\n";
    int x, y;
    char letter;

    cout << "Enter row (0-2): ";
    cin >> x;

    cout << "Enter column (0-2): ";
    cin >> y;

    cout << "Enter a letter: ";
    cin >> letter;

    return new Move<char>(x, y, letter);
}

Player<char>* WordUI::create_player(string& name, char symbol, PlayerType type) {
    if (type == PlayerType::COMPUTER) {
        return new WordComputerPlayer(symbol);
    }
    return new WordPlayer(name, symbol);
}

//-----------------------------------------------------
// WordGameManager Implementation
//-----------------------------------------------------

WordGameManager::WordGameManager(const string& dict_file) : owns_components(true) {
    board = new WordBoard(dict_file);
    ui = new WordUI();

    Player<char>** player_array = ui->setup_players();
    players[0] = player_array[0];
    players[1] = player_array[1];
    delete[] player_array;

    game = new GameManager<char>(board, players, ui);
}

WordGameManager::WordGameManager(WordBoard* b, Player<char>* p[2], WordUI* u)
    : board(b), ui(u), owns_components(true) {
    players[0] = p[0];
    players[1] = p[1];
    game = new GameManager<char>(board, players, ui);
}

WordGameManager::~WordGameManager() {
    delete game;
    if (owns_components) {
        delete players[0];
        delete players[1];
        delete ui;
        delete board;
    }
}

void WordGameManager::run() {
    game->run();
}
