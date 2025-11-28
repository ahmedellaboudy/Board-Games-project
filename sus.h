/**
 * @file SUS_Classes.h
 * @brief Defines the SUS game specific classes that extend the generic board game framework.
 *
 * This file provides:
 * - `SUS_Board`: A specialized board class for the SUS game.
 * - `SUS_UI`: A user interface class tailored to SUS game setup and player interaction.
 */

#ifndef SUS_CLASSES_H
#define SUS_CLASSES_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <string>
using namespace std;

/**
 * @class SUS_Board
 * @brief Represents the SUS game board.
 *
 * This class inherits from the generic `Board<char>` class and implements
 * the specific logic required for the SUS game, where players try to form
 * "S-U-S" sequences to score points.
 *
 * @see Board
 */
class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.
    int player1_score = 0;   ///< Score for player 1
    int player2_score = 0;   ///< Score for player 2

    /**
     * @brief Counts all S-U-S sequences for a given player symbol.
     * @param symbol The player's symbol ('S' or 'U').
     * @return The number of S-U-S sequences found.
     */
    int count_sus_sequences(char symbol);

public:
    /**
     * @brief Default constructor that initializes a 3x3 SUS board.
     */
    SUS_Board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move coordinates and symbol.
     * @return true if the move is valid and successfully applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won the game (has more S-U-S sequences).
     * @param player Pointer to the player being checked.
     * @return true if the player has won, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked.
     * @return Always returns false (not used in SUS logic).
     */
    bool is_lose(Player<char>*) { return false; }

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked.
     * @return true if all cells are filled and both players have equal scores, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (board full).
     * @param player Pointer to the player to evaluate.
     * @return true if the game has ended, false otherwise.
     */
    bool game_is_over(Player<char>* player);

    /**
     * @brief Gets the current scores for both players.
     * @return A pair containing (player1_score, player2_score).
     */
    pair<int, int> get_scores() const { return {player1_score, player2_score}; }
};


/**
 * @class SUS_UI
 * @brief User Interface class for the SUS game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * SUS-specific functionality for player setup and move input.
 *
 * @see UI
 */
class SUS_UI : public ValidatedUI<char> {
public:
    /**
     * @brief Constructs a SUS_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message for SUS game.
     */
    SUS_UI();

    /**
     * @brief Destructor for SUS_UI.
     */
    ~SUS_UI() {}

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player.
     * @param symbol Character symbol ('S' or 'U') assigned to the player.
     * @param type The type of the player (Human or Computer).
     * @return Pointer to the newly created Player<char> instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested.
     * @return A pointer to a new `Move<char>` object representing the player's action.
     */
    Move<char>* get_move(Player<char>* player);

    /**
     * @brief Displays a message showing current scores.
     * @param p1_score Player 1's score.
     * @param p2_score Player 2's score.
     */
    void display_scores(int p1_score, int p2_score);
};

#endif // SUS_CLASSES_H