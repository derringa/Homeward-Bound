/**************************************************************************
 * Program: Homeward Bound
 * Author: Andrew Derringer
**************************************************************************/

#ifndef SPACE_HPP
#define SPACE_HPP

#include "Player.hpp"

#include <string>

using std::string;



class Space
{

     protected:
          string spaceType;
          Player* doggo;

          int impedence;
          int food;
          int maxFood;
          int restock;
          bool home;

          int eventNum;

          Space* up;
          Space* right;
          Space* down;
          Space* left;

     public:
          // Loaded  Constructor
          // set player and event to nullptr, set home to false
          // use additional member function to set impedence and food by spaceType.
          Space(Space*, Space*, Space*, Space*);

          // destructor
          virtual ~Space() = 0;

          // Member functions
          Player* getPlayer();
          void setPlayer(Player*);
          //Event* getEvent();
          //void setEvent(Event*);
          //void playEvent(); // Print message to user, change stats and inventory accordingly.
          int getImpedence(); // for determining how many steps doggo will lose.
          int getFood(); // for determining how much food doggo will gain.
          void setFood(int); // for changing after doggo eats the food or stores it.
          void restoreFood(); // food++ if less than max.
          int getMaxFood();
          void makeHome();
          bool isHome();

          void setUp(Space*);
          Space* getUp();
          void setRight(Space*);
          Space* getRight();
          void setDown(Space*);
          Space* getDown();
          void setLeft(Space*);
          Space* getLeft();

          virtual void printHeader();
          virtual void printType();
          virtual void printKibble();
          virtual void printSpacer();

          void setEvent(int);
          int getEvent();
};

#endif
