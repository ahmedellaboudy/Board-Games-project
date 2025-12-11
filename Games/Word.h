#ifndef _WORD_H
#define _WORD_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <fstream>
#include <algorithm>
#include <cctype>
#include <set>

/**
 * @brief Board class for Word Tic-Tac-Toe game
 *
 * A 3x3 grid where players place letters to form valid 3-letter words
 * horizontally, vertically, or diagonally.
 */
class WordBoard : public Board<char> {
private:
    set<string> dictionary; ///< Set of valid 3-letter words

    /**
     * @brief Load dictionary from file
     * @param filename Path to dictionary file
     */
    void load_dictionary(const string& filename);

    /**
     * @brief Check if a word is valid
     * @param word The word to check
     * @return true if word exists in dictionary
     */
    bool is_valid_word(const string& word) const;

    /**
     * @brief Extract word from board at given position and direction
     * @param row Starting row
     * @param col Starting column
     * @param dr Row delta (-1, 0, 1)
     * @param dc Column delta (-1, 0, 1)
     * @return Extracted word as string
     */
    string extract_word(int row, int col, int dr, int dc) const;

    /**
     * @brief Check if there's a valid word on the board
     * @return true if any valid word is found
     */
    bool has_valid_word() const;

public:
    /**
     * @brief Construct a WordBoard with dictionary
     * @param dict_file Path to dictionary file (default: "dic.txt")
     */
    WordBoard(const string& dict_file = "dic.txt");

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

/**
 * @brief Human player for Word Tic-Tac-Toe
 */
class WordPlayer : public Player<char> {
public:
    WordPlayer(string name, char symbol);
};

/**
 * @brief Computer player for Word Tic-Tac-Toe
 */
class WordComputerPlayer : public Player<char> {
public:
    WordComputerPlayer(char symbol);
};

/**
 * @brief UI class for Word Tic-Tac-Toe game
 */
class WordUI : public ValidatedUI<char> {
public:
    WordUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

/**
 * @brief Game Manager wrapper for Word Tic-Tac-Toe
 * Handles game initialization and cleanup
 */
class WordGameManager {
private:
    WordBoard* board;
    WordUI* ui;
    Player<char>* players[2];
    GameManager<char>* game;
    bool owns_components; ///< Flag to track if manager owns the components

public:
    /**
     * @brief Constructor - initializes all game components internally
     * @param dict_file Path to dictionary file
     */
    WordGameManager(const string& dict_file = "dic.txt");

    /**
     * @brief Constructor - uses externally provided components
     * @param b Board pointer
     * @param p Array of player pointers
     * @param u UI pointer
     */
    WordGameManager(WordBoard* b, Player<char>* p[2], WordUI* u);

    /**
     * @brief Destructor - cleans up allocated memory
     */
    ~WordGameManager();

    /**
     * @brief Run the game
     */
    void run();
};

#endif // _WORD_H
