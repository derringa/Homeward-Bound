/**************************************************************************
 * Program: Homeward Bound
 * Author: Andrew Derringer
**************************************************************************/

#ifndef FOREST_HPP
#define FOREST_HPP

#include "Space.hpp"



class Forest : public Space
{
     public:
          // Loaded Constructor
          Forest(Space*, Space*, Space*, Space*);
          // Destructor
          virtual ~Forest();

          virtual void printType();
          virtual void printKibble();
          virtual void printSpacer();
};

#endif
