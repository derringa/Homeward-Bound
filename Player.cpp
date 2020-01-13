/**************************************************************************
 * Program: Homeward Bound
 * Author: Andrew Derringer
**************************************************************************/

#include "Player.hpp"
#include "inputValidation.hpp"

#include <iostream>



/**************************************************************************
 * Passed: string for doggo's name
 * Returns:
 * Description: Initial feature that has yet to be implemented.
**************************************************************************/
Player::Player(string inName)
{
     name = inName;
     moves = 8;
     maxMoves = 8;
     food = 14;
     maxFood = 14;
     row = 0;
     column = 0;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
Player::~Player() {}



/**************************************************************************
 * Passed
 * Returns:i string for player's name.
 * Description: Initial feature that has yet to be implemented.
**************************************************************************/
string Player::getName()
{
     return name;
}



/**************************************************************************
 * Passedi: int associated with characteristics within the player class
 * Returns: bool T/F items was added
 * Description: Inventory maxes out at 3 so player must choose to delete
 * an old item using member fxn deleteItem() or not add the item. If the
 * item was not added then it stays on the board.
**************************************************************************/
bool Player::addInventoryItem(int item)
{
     bool addItem = false;

     // Member fxn that prints a message unique to each item number
     printNarrative(item);

     // determine if the user even wants to add the item
     std::cout << std::endl << std::endl
               << "Would you like to add " << printItem(item)
               << " to yout inventory?" << std::endl;
     addItem = boolValidate();

     // if yes then check inventory size.
     if(addItem)
     {
          // if inventory full offer to delete something
          if(inventory.size() >= 3)
          {
               std::cout << "Please select an item number to delete to make room for "
                         << printItem(item) << std::endl
                         << "or select 6 to cancel:" << std::endl << std::endl;

               printInventory();

               std::cout << std::endl << std::endl;

               int deleteChoice = integerRangeValidate("Error. You must select a listed item number. Try again:", 1,6);

               // 6 associated with choosing not to delete anything. Anything else deletes
               if(deleteChoice != 6)
               {
                    std::cout << "Item " << printItem(deleteChoice) << " was deleted."
                              << std::endl;
                    // sends the index number of the item to delete
                    deleteInventoryItem(deleteChoice);
                    // adds new item to the back of the inventory.
                    inventory.push_back(item);
               // Any other option passes
               }else{
                    std::cout << "Canceled... New item was not added." << std::endl;
                    addItem = false;
               }
          }else{
               inventory.push_back(item);
          }
     // if the user chooses not to add the item then it says so. no action taken
     }else{
          std::cout << "Item " << printItem(item) << " was not added." << std::endl;
          addItem = false;
     }

     // items come with certain bonuses and if chosen to add the player is affected.
     // switch statement cases associated with item number.
     if(addItem)
     {
          switch(item)
          {
               case 1: break;
               case 2: maxMoves += 2;
                       break;
               case 3: maxFood += 5;
                       break;
               case 4: maxFood += 2;
                       break;
               case 5: maxMoves += 5;
          }
     }

     return addItem;
}





/**************************************************************************
 * Passed: integer of item index in inventory
 * Returns:
 * Description: Does NOT receive item number but index number. Learned this
 * the hard way.
**************************************************************************/
void Player::deleteInventoryItem(int index)
{

     // iterates to that index
     list<int>::iterator it = inventory.begin();
     advance(it, index - 1);

     // saves the value in the index before deleting for use in upcoming switch
     int item = *it;
     inventory.erase(it);

     // item value used to remove bonues that that item provided.
     switch(item)
     {
          case 1: break;
          case 2: maxMoves -= 2;
                  break;
          case 3: maxFood -= 5;
                  break;
          case 4: maxFood -= 2;
                  break;
          case 5: maxMoves -= 5;
     }
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description: Prints all items currently in inventory using the print item
 * member fxn for each item.
**************************************************************************/
void Player::printInventory()
{
     int count = 1;

     for(auto i = inventory.begin(); i != inventory.end(); i++)
     {
          std::cout << count << ") " << printItem(*i) << "   ";
          count++;
     }
}



/**************************************************************************
 * Passed: integer item identification number
 * Returns:
 * Description: prints title of item associated with that number.
**************************************************************************/
string Player::printItem(int item)
{
     string itemName;

     switch(item)
     {
          case 1: itemName = "Fluffy!";
                  break;
          case 2: itemName = "Dog Boots (Max Moves + 2)";
                  break;
          case 3: itemName = "Dog Pack (Max Food + 5)";
                  break;
          case 4: itemName = "Collapsable Bowl (Max Food + 2)";
                  break;
          case 5: itemName = "SkateBoard (Max Moves + 5)";
     }

     return itemName;
}



/**************************************************************************
 * Passed: integer item identification number.
 * Returns:
 * Description: prints event message when associating with that item.
**************************************************************************/
void Player::printNarrative(int item)
{
     switch(item)
     {
          case 1: std::cout << "You found Fluffy!";
                  break;
          case 2: std::cout << "Some rad backpackers gave you an extra pair of "
                            << printItem(item) << "."; 
                  break;
          case 3: std::cout << "You made friends with an Aussie who gifted you her "
                            << printItem(item) << "!"; 
                  break;
          case 4: std::cout << "A trucker at the local pump shared his food and left you a "
                            << printItem(item) << "."; 
                  break;
          case 5: std::cout << "The kids at the skate park showed you a few tricks and gave you your very own "
                            << printItem(item) << "!"; 
     }
}



/**************************************************************************
 * Passed:
 * Returns: bool T/F if player possess fluffy
 * Description: Need fluffy to win so we check for her.
**************************************************************************/
bool Player::hasFluffy()
{
     bool gotHer = false;

     for(auto i = inventory.begin(); i != inventory.end(); i++)
     {
          // if whats in that list index = fluffy item ID then true.
          if(*i == 1)
          {
               gotHer = true;
          }
     }

     return gotHer;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
int Player::getMoves()
{
     return moves;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Player::setMoves(int inputMoves)
{
     moves = inputMoves;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Player::decreaseMoves(int spaceImpedence)
{
     moves -= spaceImpedence;

     if(moves < 0)
     {
          moves = 0;
     }
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Player::refreshMoves()
{
     moves = maxMoves;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
int Player::getMaxMoves()
{
     return maxMoves;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Player::increaseMaxMoves(int movesBonus)
{
     maxMoves += movesBonus;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
int Player::getFood()
{
     return food;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Player::increaseFood(int spaceFood)
{
     food += spaceFood;

     if(food > maxFood)
     {
          food = maxFood;
     }
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Player::movementCost()
{
     food -= 2;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
int Player::getMaxFood()
{
     return maxFood;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Player::increaseMaxFood(int foodBonus)
{
     maxFood += foodBonus;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
int Player::getRow()
{
     return row;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Player::setRow(int inRow)
{
     row = inRow;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
int Player::getColumn()
{
     return column;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Player::setColumn(int inColumn)
{
     column = inColumn;
}
