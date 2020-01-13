/**************************************************************************
 * Program: Homeward Bound
 * Author: Andrew Derringer
**************************************************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <list>

using std::string;
using std::list;



class Player
{

     private:
          string name;
          list <int> inventory;
          int moves;
          int maxMoves;
          int food;
          int maxFood;

          int row;
          int column;

     public:
          // Loaded  Constructor
          Player(string);

          // destructor
          ~Player();

          string getName();

          bool addInventoryItem(int);
          void deleteInventoryItem(int);
          void printInventory();
          string printItem(int);
          void printNarrative(int);
          bool hasFluffy();

          int getMoves();
          void setMoves(int);
          void decreaseMoves(int);
          void refreshMoves();
          int getMaxMoves();
          void increaseMaxMoves(int);

          int getFood();
          void increaseFood(int);
          void movementCost();
          int getMaxFood();
          void increaseMaxFood(int);

          int getRow();
          void setRow(int);
          int getColumn();
          void setColumn(int);
};

#endif
