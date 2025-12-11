/**
* @file sus.h
 * @brief Defines the SUS game specific classes that extend the generic board game framework.
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
 */
class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.';
    int player1_score = 0;
    int player2_score = 0;

    int count_sus_sequences(char symbol);

public:
    SUS_Board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; }
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    pair<int, int> get_scores() const { return {player1_score, player2_score}; }
};

/**
 * @class SUS_UI
 * @brief User Interface class for the SUS game.
 */
class SUS_UI : public ValidatedUI<char> {
public:
    SUS_UI();
    ~SUS_UI() {}

    /**
     * @brief Creates a player (Human or AI only - no random computer)
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Setup players with AI option (no random computer option)
     */
    Player<char>** setup_players() override;

    Move<char>* get_move(Player<char>* player);
    void display_scores(int p1_score, int p2_score);

protected:
    /**
     * @brief Override to show only Human and AI options
     */
    PlayerType get_player_type_choice(string player_label, const vector<string>& options) override;
};

#endif // SUS_CLASSES_H