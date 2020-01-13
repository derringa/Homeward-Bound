/**************************************************************************
 * Program: Homeward Bound
 * Author: Andrew Derringer
**************************************************************************/

#include "Desert.hpp"



/**************************************************************************
 * Passed: 
 * Returns:
 * Description:
**************************************************************************/
Desert::Desert(Space* inUp, Space* inRight, Space* inDown, Space* inLeft) : Space(inUp, inRight, inDown, inLeft)
{
     spaceType = "D";
     impedence = 2;
     food = 0;
     maxFood = 0;
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
Desert::~Desert() {}
