/**************************************************************************
 * Program: Homeward Bound
 * Author: Andrew Derringer
**************************************************************************/

#include "Board.hpp"
#include "helperFunctions.hpp"
#include "Water.hpp"
#include "Plains.hpp"
#include "Forest.hpp"
#include "Mountain.hpp"
#include "Desert.hpp"

#include <iostream>



/**************************************************************************
 * Passed:
 * Returns: 
 * Description:
**************************************************************************/
Board::Board(string playerName, int inTurns, int inColumns, int inRows, int numEvents)
{
     turns = inTurns;
     columns = inColumns;
     rows = inRows;

     head = nullptr;
     doggo = new Player(playerName);

     populateBoard();
     setStart();
     setEnd();
     populateEvents(numEvents);
}



/**************************************************************************
 * Passed:
 * Returns: 
 * Description:
**************************************************************************/
Board::~Board()
{
     // also held by a space at any time but deleted here.
     delete doggo;

     Space* currentSpace = head;
     Space* nextRow;

     while(currentSpace != nullptr)
     {
          nextRow = currentSpace->getDown();

          while(currentSpace != nullptr)
          {
               Space* garbage = currentSpace;
               currentSpace = currentSpace->getRight();

               delete garbage;
               garbage = nullptr;
          }

          currentSpace = nextRow;
     }
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description: Generates a randomized board depending on desired rows and columns
**************************************************************************/
void Board::populateBoard()
{
     int spaceType = getRandomInteger(1,3);
     int currentType = spaceType;
     int chanceChange = 1;

     // Generate an initial space for upcoming with crawling though and generating the other spaces
     head = generateSpace(spaceType, nullptr, nullptr, nullptr, nullptr);

     Space* currentColumn = head;
     Space* currentSpace = head;
     Space* adjacentSpace = nullptr;

     // head already at first column and row and each incrememt reaches one column farther out so we
     // use < columns - 1.
     for(int col = 0; col < columns - 1; col++)
     {
          for(int row = 0; row < rows; row++)
          {
               // We have a space type generator whose odds of changing get greater over time
               spaceType = changeSpaceType(spaceType, chanceChange);

               // first column creates a space down and to the right except for very last rown in column
               if(col == 0 && row < rows - 1)
               {
                    spaceType = changeSpaceType(spaceType, 30);
                    currentSpace->setDown(generateSpace(spaceType, currentSpace, nullptr, nullptr, nullptr));
                    spaceType = changeSpaceType(spaceType, chanceChange);
                    currentSpace->setRight(generateSpace(spaceType, adjacentSpace, nullptr, nullptr, currentSpace));
                    if(adjacentSpace != nullptr)
                    {
                         adjacentSpace->setDown(currentSpace->getRight());
                    }
                    adjacentSpace = currentSpace->getRight();
               //top rows don't need to connect their right space to a space above it.
               }else if(col > 0 && row == 0){
                    currentSpace->setRight(generateSpace(spaceType, nullptr, nullptr, nullptr, currentSpace));
                    adjacentSpace = currentSpace->getRight();
               // but everything else needs to use the saved adjacent space to connect their new right neighbor.
               }else{
                    currentSpace->setRight(generateSpace(spaceType, adjacentSpace, nullptr, nullptr, currentSpace));
                    adjacentSpace->setDown(currentSpace->getRight());
                    adjacentSpace = currentSpace->getRight();
               }



               if(spaceType != currentType)
               {
                    chanceChange = 1;
                    currentType = spaceType;
               }else{
                    chanceChange += 1;
               }

               currentSpace = currentSpace->getDown();
          }

          currentColumn = currentColumn->getRight();
          currentSpace = currentColumn;
     }
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
void Board::populateEvents(int maxEvents)
{
     
     Space* currentSpace;
     int randX;
     int randY;

     int eventsList[] = {1, 2, 3, 4, 5, 6, 6, 6, 6, 7, 7, 7};

     for(int i = 0; i < maxEvents; i++)
     {
          currentSpace = head;
          randX = getRandomInteger(0, columns - 1);
          randY = getRandomInteger(0, rows - 1);

          for(int col = 0; col < randX; col++)
          {
               currentSpace = currentSpace->getRight();
          }
          for(int row = 0; row < randY; row++)
          {
               currentSpace = currentSpace->getDown();
          }

          if(currentSpace->getEvent() == 0 && currentSpace->getPlayer() == nullptr && !(currentSpace->isHome()))
          {
               currentSpace->setEvent(eventsList[i]);
          }
     }
}

         

/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
Space* Board::generateSpace(int spaceType, Space* inUp, Space* inRight, Space* inDown, Space* inLeft)
{
     Space* tempSpace;

     switch(spaceType)
     {
          case 1: tempSpace = new Plains(inUp, inRight, inDown, inLeft);
                  break;
          case 2: tempSpace = new Forest(inUp, inRight, inDown, inLeft);
                  break;
          case 3: tempSpace = new Desert(inUp, inRight, inDown, inLeft);
     }

     return tempSpace;
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
int Board::changeSpaceType(int currentType, int percentChance)
{
     int newType = currentType;
     int changeType = getRandomInteger(1,100);

     if(changeType <= percentChance)
     {
          newType = getRandomInteger(1,3);
     }

     return newType;
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
void Board::setStart()
{
     int start = getRandomInteger(0, rows - 1);
     Space* currentSpace = head;

     for(int row = 0; row < start; row++)
     {
          currentSpace = currentSpace->getDown();
     }

     currentSpace->setPlayer(doggo);
     doggo->setRow(start);

     currentSpace->setFood(0);
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
void Board::setEnd()
{
     int end = getRandomInteger(0, rows - 1);
     Space* currentSpace = head;

     while(currentSpace->getRight() != nullptr)
     {
          currentSpace = currentSpace->getRight();
     }

     for(int row = 0; row < end; row++)
     {
          currentSpace = currentSpace->getDown();
     }

     currentSpace->makeHome();
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
bool Board::movePlayer(int direction)
{
     bool changeSpace = false;
     Space* currentSpace = head;

     for(int col = 0; col < doggo->getColumn(); col++)
     {
          currentSpace = currentSpace->getRight();
     }
     for(int row = 0; row < doggo->getRow(); row++)
     {
          currentSpace = currentSpace->getDown();
     }

     Space* newSpace = currentSpace;

     switch(direction)
     {
          case 1: if(currentSpace->getUp() != nullptr)
                    {
                         newSpace = currentSpace->getUp();
                         doggo->setRow(doggo->getRow() - 1);
                         changeSpace = true; 
                    }
                    break;
          case 2: if(currentSpace->getRight() != nullptr)
                    {
                         newSpace = currentSpace->getRight();
                         doggo->setColumn(doggo->getColumn() + 1);
                         changeSpace = true; 
                    }
                    break;
          case 3: if(currentSpace->getDown() != nullptr)
                    {
                         newSpace = currentSpace->getDown();
                         doggo->setRow(doggo->getRow() + 1);
                         changeSpace = true; 
                    }
                    break;
          case 4: if(currentSpace->getLeft() != nullptr)
                    {
                         newSpace = currentSpace->getLeft();
                         doggo->setColumn(doggo->getColumn() - 1);
                         changeSpace = true; 
                    }
     }

     if(newSpace != currentSpace)
     {
          newSpace->setPlayer(doggo);
          currentSpace->setPlayer(nullptr);

          doggo->decreaseMoves(newSpace->getImpedence());
          doggo->increaseFood(newSpace->getFood());
          doggo->movementCost();
          newSpace->setFood(0);
     }

     return changeSpace;
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
void Board::playEvent()
{
     Space* currentSpace = head;

     for(int col = 0; col < doggo->getColumn(); col++)
     {
          currentSpace = currentSpace->getRight();
     }
     for(int row = 0; row < doggo->getRow(); row++)
     {
          currentSpace = currentSpace->getDown();
     }

     int item = currentSpace->getEvent();

     if(item > 0 && item < 6)
     {
          system("clear");

          bool addItem = doggo->addInventoryItem(item);
          if(addItem)
          {
               currentSpace->setEvent(0);
          }

          pauseUntilInput();
     }else if(item == 6){
          system("clear");

          std::cout << "You came across a Golden Doodle litter reunion party!" << std::endl
               << "They shared their kibble and restored your food count to max." << std::endl;
          doggo->increaseFood(doggo->getMaxFood());

          currentSpace->setEvent(0);
          pauseUntilInput();
     }else if(item == 7){
          system("clear");

          std::cout << "You stumple upon a goat yoga session. The instructor welcomes you" << std::endl
               << "and now you're feeling refreshed. Move count restored to max" << std::endl;

          currentSpace->setEvent(0);
          pauseUntilInput();
     }

}
    


/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
int Board::getTurns()
{
     return turns;
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
int Board::getColumns()
{
     return columns;
}



/**************************************************************************
 * Passed:
 * Returns:
 * Description:
**************************************************************************/
int Board::getRows()
{
     return rows;
}



/**************************************************************************
 * Passed:
 * Returns: 
 * Description:
**************************************************************************/
void Board::printBoard()
{
     Space* currentSpace = head;
     Space* startRow = currentSpace;
     Space* nextRow;

     while(currentSpace != nullptr)
     {
          nextRow = currentSpace->getDown();

          while(currentSpace != nullptr)
          {
               if(currentSpace->getPlayer() != nullptr)
               {
                    std::cout << "*~~~~*";
               }else{
                    currentSpace->printHeader();
               }
               currentSpace = currentSpace->getRight(); 
          }
 
          currentSpace = startRow;
          std::cout << std::endl;

          while(currentSpace != nullptr)
          {
               currentSpace->printSpacer();
               currentSpace = currentSpace->getRight();
          }
 
          currentSpace = startRow;
          std::cout << std::endl;
 
          while(currentSpace != nullptr)
          {
               if(currentSpace->getPlayer() != nullptr)
               {
                    std::cout << "| UR |";
               }else if(currentSpace->isHome()){
                    std::cout << "|COME|";
               }else{
                    currentSpace->printType();
               }
               currentSpace = currentSpace->getRight(); 
          }

          currentSpace = startRow;
          std::cout << std::endl;

          while(currentSpace != nullptr)
          {
               if(currentSpace->getPlayer() != nullptr)
               {
                    std::cout << "|HERE|";
               }else if(currentSpace->isHome()){
                    std::cout << "|HOME|";
               }else{
                    currentSpace->printKibble();
               }
               currentSpace = currentSpace->getRight();
 
          }

          currentSpace = startRow;
          std::cout << std::endl;

          while(currentSpace != nullptr)
          {
               if(currentSpace->getEvent() != 0)
               {
                    std::cout << "|EVNT|";
               }else{
                    currentSpace->printSpacer();
               }
               currentSpace = currentSpace->getRight();
          }
 
          currentSpace = startRow;
          std::cout << std::endl;

          while(currentSpace != nullptr)
          {
               if(currentSpace->getPlayer() != nullptr)
               {
                    std::cout << "*~~~~*";
               }else{
                    currentSpace->printHeader();
               }
               currentSpace = currentSpace->getRight(); 
          }
          std::cout << std::endl;

          currentSpace = nextRow;
          startRow = currentSpace;
     }
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Board::turnMaintenance()
{
     doggo->refreshMoves();

     Space* currentSpace = head;
     Space* nextRow;

     while(currentSpace != nullptr)
     {
          nextRow = currentSpace->getDown();

          while(currentSpace != nullptr)
          {
               currentSpace->restoreFood();
               currentSpace = currentSpace->getRight();
          }

          currentSpace = nextRow;
     }
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
bool Board::endOfTurn()
{
     bool end = false;

     if(doggo->getMoves() <= 0)
     {
          end = true;
     }

     return end;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
bool Board::isDead()
{
     bool dead = false;

     if(doggo->getFood() < 0)
     {
          dead = true;
     }

     return dead;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
bool Board::wonGame()
{
     Space* currentSpace = head;
     bool hasWon = false;


     for(int col = 0; col < doggo->getColumn(); col++)
     {
          currentSpace = currentSpace->getRight();
     }
     for(int row = 0; row < doggo->getRow(); row++)
     {
          currentSpace = currentSpace->getDown();
     }

     if(doggo->hasFluffy() && currentSpace->isHome())
     {
          system("clear");

          std::cout << "You made it back to the family with Fluffy..." << std::endl
                    << "You're a hero!" << std::endl << std::endl;
          hasWon = true;
     }else if(!(doggo->hasFluffy()) && currentSpace->isHome()){
          system("clear");
    
          std::cout << "You can see home from here, but where is fluffy?" << std::endl
                    << "You can't just leave her out there. Go get her!" << std::endl << std::endl;

          pauseUntilInput();
     }

     return hasWon;
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Board::playerStatus()
{
     std::cout << "Moves: " << doggo->getMoves() << "  "
               << "Food: " << doggo->getFood() << "  "
               << "Total Turns: " << turns << std::endl
               << "Inventry: ";

     doggo->printInventory();
}



/**************************************************************************
 * Passed
 * Returns:
 * Description:
**************************************************************************/
void Board::clearMoves()
{
     doggo->setMoves(0);
}



