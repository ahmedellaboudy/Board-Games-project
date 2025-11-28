#ifndef XO_5X5_CLASSES_H
#define XO_5X5_CLASSES_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Represents the game board for 5x5 Three-in-a-Row
 */
class XO_5x5_Board : public Board<char> {
private:
    /**
     * @brief Counts all three-in-a-row sequences for a given symbol (horizontal, vertical, and diagonals)
     * @param symbol The symbol to count sequences for (X or O)
     * @return Number of three-in-a-row sequences
     */
    int count_three_in_row(char symbol);

public:
    /**
     * @brief Constructor - creates 5x5 board
     */
    XO_5x5_Board();

    /**
     * @brief Updates the board with a move
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if a player has the most three-in-a-row sequences (win condition)
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief In this game, no direct lose condition - always returns false
     */
    bool is_lose(Player<char>* player) override { return false; }

    /**
     * @brief Game ends in draw when both players have equal three-in-a-row sequences
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Game is over when 24 moves are made
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Displays the scores for both players
     */
    void display_scores(Player<char>* player1, Player<char>* player2);

    /**
     * @brief Get number of moves made
     */
    int get_moves_count() const { return n_moves; }
};

//-----------------------------------------------------

/**
 * @brief UI for XO_5x5 game
 */
class XO_5x5_UI : public ValidatedUI<char> {
public:
    /**
     * @brief Constructor
     */
    XO_5x5_UI();

    /**
     * @brief Gets move from player
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Creates a player with given parameters
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Sets up players for the game
     */
    Player<char>** setup_players() override;

    /**
     * @brief Displays final scores
     */
    void display_final_scores(int scoreX, int scoreO, const string& playerX, const string& playerO);
};

//-----------------------------------------------------

/**
 * @brief Game Manager for XO_5x5 game
 */
class XO_5x5_GameManager {
private:
    XO_5x5_Board* board;
    Player<char>* players[2];
    XO_5x5_UI* ui;

public:
    /**
     * @brief Constructor
     */
    XO_5x5_GameManager();

    /**
     * @brief Destructor
     */
    ~XO_5x5_GameManager();

    /**
     * @brief Runs the game
     */
    void run();
};

#endif // XO_5X5_CLASSES_H