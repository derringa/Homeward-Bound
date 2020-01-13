/**************************************************************************
 * Program: Homeward Bound
 * Author: Andrew Derringer
**************************************************************************/

#ifndef DESERT_HPP
#define DESERT_HPP

#include "Space.hpp"



class Desert : public Space
{
     public:
          // Loaded Constructor
          Desert(Space*, Space*, Space*, Space*);
          // Destructor
          virtual ~Desert();
};

#endif
