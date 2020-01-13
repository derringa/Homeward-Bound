/**************************************************************************
 * Program: Homeward Bound
 * Author: Andrew Derringer
**************************************************************************/

#ifndef PLAINS_HPP
#define PLAINS_HPP

#include "Space.hpp"



class Plains : public Space
{
     public:
          // Loaded Constructor
          Plains(Space*, Space*, Space*, Space*);
          // Destructor
          virtual ~Plains();

          virtual void printType();
          virtual void printKibble();
          virtual void printSpacer();
};

#endif
