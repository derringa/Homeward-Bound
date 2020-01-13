/**************************************************************************
 * Program: Homeward Bound
 * Author: Andrew Derringer
**************************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

#include "Space.hpp"
#include "Player.hpp"

#include <string>

using std::string;



class Board
{
     private:
          Space* head;
          Player* doggo;
          int turns;
          int columns;
          int rows;

     public:
          // Loaded Constructor
          Board(string, int, int, int, int);
          //Destructor
          ~Board();

          // Member Functions
          void populateBoard(); // Called in constructor to generate spaces
          Space* generateSpace(int, Space*, Space*, Space*, Space*); // for generating a board of random space types
          int changeSpaceType(int, int); // used when generating the board for odds of changing space type
          void setStart(); // Make random starting space hold player
          void setEnd(); // randomly select end location for home
          void populateEvents(int);
          bool movePlayer(int); // make new space hold player, set previous to null, change row and column value in player
          //player* getPlayer(); // may be useful for actions in main or moving player
          void playEvent();
          int getTurns(); // for game flow in main
          int getColumns(); // for game flow in main
          int getRows(); // for game flow in main
          void printBoard();

          void turnMaintenance();
          bool endOfTurn();
          bool isDead();
          bool wonGame();
          void playerStatus();
          void clearMoves();

};

#endif
