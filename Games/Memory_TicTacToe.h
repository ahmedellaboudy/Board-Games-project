#ifndef MEMORY_TICTACTOE_H
#define MEMORY_TICTACTOE_H

#include "BoardGame_Classes.h"
#include "ValidatedUI.h"
#include <string>

using namespace std;

/**
 * @class Fake_Board
 * @brief A board that displays '?' for empty cells
 */
class Fake_Board : public Board<char> {
private:
    char blank_symbol = '?';  // Changed to '?' instead of ' '

public:
    Fake_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>*) override;
    bool is_lose(Player<char>*) override;
    bool is_draw(Player<char>*) override;
    bool game_is_over(Player<char>*) override;
};

class Memory_Board : public Board<char> {
private:
    char blank_symbol = ' ';
    bool has_three_in_row(char symbol);

public:
    Memory_Board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class Memory_UI : public ValidatedUI<char> {
public:
    Memory_UI();
    ~Memory_UI() {}
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif
