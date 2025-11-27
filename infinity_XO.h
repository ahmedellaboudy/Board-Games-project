//@file Infinity_XO_Classes.h
//@brief Defines the Infinity Tic-Tac-Toe game classes.
#ifndef INFINITY_XO_CLASSES_H
#define INFINITY_XO_CLASSES_H

#include "BoardGame_Classes.h"
#include <queue>
using namespace std;


 //* @class Infinity_X_O_Board
 //* @brief Represents the Infinity Tic-Tac-Toe game board.
 
class infinity_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character for empty cell
    queue<pair<int, int>> history; ///< Track move history
  
public:
    
    /* @brief Default constructor that initializes a 3x3 board.*/
     
    infinity_Board();

     //* @brief Updates the board with a player's move.
    bool update_board(Move<char>* move);

    //@brief Removes the oldest move from the board.

    void remove_oldest_move();

    
 /*   @brief Checks if the given player has won the game.*/
    
    bool is_win(Player<char>* player);

    
     //@brief Checks if the given player has lost the game.
     
    bool is_lose(Player<char>*) { return false; };

  /*   @brief Checks if the game has ended in a draw.*/
     
    bool is_draw(Player<char>* player);

    /*@brief Determines if the game is over (win or draw).*/

    bool game_is_over(Player<char>* player);

};


 //@class Infinity_XO_UI
 //@brief User Interface class for the Infinity Tic-Tac-Toe game.

class infinity_UI : public UI<char> {
public:
     /*@brief Constructs an Infinity_XO_UI object.*/
    
    infinity_UI();

    
     //@brief Destructor for Infinity_XO_UI.

    ~infinity_UI() {};

    // @brief Creates a player of the specified type.


    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     */

    
    
    virtual Move<char>* get_move(Player<char>* player);
};

#endif // INFINITY_XO_CLASSES_H