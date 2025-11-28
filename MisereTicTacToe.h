#ifndef MISERE_TIC_TAC_TOE_H
#define MISERE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <string>

class MisereTicTacToe_board : public Board {
public:
    MisereTicTacToe_board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_valid_adjacent_move(int from_x, int from_y, int to_x, int to_y);
    std::vector<Move<char>*> get_possible_moves(Player<char>* player);
};

class MisereTicTacToeUI : public UI<char> {
public:
    MisereTicTacToeUI();
    ~MisereTicTacToeUI();
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    Move<char>* get_move_with_source(Player<char>* player);
};

#endif
