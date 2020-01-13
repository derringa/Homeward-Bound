/**************************************************************************
 * Program: Homeward Bound
 * Author: Andrew Derringer
 * Date: 3/19/2019
 * Description: Game where a dog has to make it home from one side of a 
 * 2D linked list to the other. Each space has special characteristics
 * associated with desert, plains, or forest. A selection of events are also
 * generated throughout the map including finding you missing family Fluffy
 * the cat! The game cannot be completed without returning to the home
 * square with fluffy in your inventory. Losing conditions include running
 * out of turns or running out of food at any time.
**************************************************************************/

#include "inputValidation.hpp"
#include "helperFunctions.hpp"
#include "Space.hpp"
#include "Water.hpp"
#include "Plains.hpp"
#include "Forest.hpp"
#include "Mountain.hpp"
#include "Desert.hpp"
#include "Board.hpp"

#include <iostream>
#include <ctime>
#include <limits>

using std::cout;
using std::endl;
using std::cin;


int main()
{
     std::srand(std::time(0));

     // Passed to menu writing function for navigation through the map.
     string actions[] = {"Move Up", "Move Right", "Move Down", "Move Left"};


     system("clear");

     // Introduction page: Provides theme and asks the user if they want to play.
     cout << "+----------------------------------------------------------------+" << endl
          << "|                         HOMEWARD BOUND                         |" << endl
          << "+----------------------------------------------------------------+" << endl
          << endl << endl;

     cout << "Hey there lil' doggy. You musta got lost while your family" << endl
          << "was on a campin' trip. Heard'm hootin' and hollarin' your" << endl
          << "name all day before they finally gave up and scooted home." << endl
          << endl
          << "Even worse, it sounded like the family cat got loose at the" << endl
          << "same dang time! It's a darn shame to lose 1 family member." << endl
          << "But 2 in one go? You can't make up somethin' that tragic." << endl
          << endl
          << "Looks like that there family was a keeper. I would do just" << endl
          << "anything to have one of my own. Think you can make it back" << endl
          << "to yours before winter sets in?" << endl
          << endl;

     // Enters outer most loop of generating a new board and player if true.
     cout << "Would you like to play?" << endl;
     bool play = boolValidate();



     while(play)
     {
          // New board and player generated.
          Board game("Bella", 20, 25, 6, 12);
          int turn = 1;

          system("clear");

          // Explains navigation and objective to complete the game.
          cout << "+----------------------------------------------------------------+" << endl
               << "|                         HOMEWARD BOUND                         |" << endl
               << "+----------------------------------------------------------------+" << endl
               << endl << endl;

          cout << "Yeehaw! Somthin' that special is worth fightin' for." << endl
               << "I got a gift for you. It ain't fancy but it's all I got." << endl
               << "Look now, it's a map! Let me give you some pointers on" << endl
               << "how to use it." << endl
               << endl << endl;

          cout << "+----+      Each square is a land type with special features." << endl
               << "|@@@@| <--- Here is type Forest = @@, Plains = ><, desert = blank" << endl
               << "| F2 | <--- Letter is type again and # is move cost for that space" << endl
               << "| K3 | <--- K = kibble and that # is how much grub you'll find." << endl
               << "|EVNT| <--- Some spaces are marked for special events or items!" << endl
               << "+----+      but we won't know what they are until you take a peek." << endl
               << endl << endl;

          cout << "You'll see us over here on the far left marked with a big \"UR HERE\"" << endl
               << "And judging by their direction. I'd assume the family is on the far right." << endl
               << "Make sure to keep watch of your food rations and how much time you" << endl
               << "got left 'til winter comes a knockin." << endl
               << endl
               << "And one more thing. If you're gonna do this then you gotta do it right!" << endl
               << "For the family, you know? Your momma was all in tears over that poor" << endl
               << "cat friend of yours. Fluffy was her name? I reckon it just won't be the" << endl
               << "same back home without her. Why don't you check out some events and see" << endl
               << "if they'll lead you back to the old girl, hey?" << endl
               << endl;

          cout << "Well that'll about do it lil' doggy. Good luck and bring the pretty family" << endl
               << "of yours back together safe now, you hear?" << endl
               << endl;

          pauseUntilInput();


          // Middle Loop: Each turn allows a certain amount of movement. The outter loop iterates
          // when movement = 0 while the innter most loop iterates after the player moves to a new
          // space and movement is decrememted but hasn't reached 0.
          while(turn <= game.getTurns())
          {

               // Inner most loop print the board, inventory, and navigation.
               // It checks at each move if the player has "starved" or has made it home.
               // Under any game ending condition it sets movement left to 0 to exit the inner loop
               // and sets the turn to total + 1 to exit the middle loop.
               while(!(game.endOfTurn()))
               {

                    if(game.isDead())  // if starved
                    {
                         system("clear");

                         cout << "Oh no! You ran out of food for your journey." << endl
                              << "You better rest up so you can try again next time..." << endl << endl
                              << "GAME OVER" << endl << endl;
                         turn = game.getTurns() + 1; // exit middle loop
                         game.clearMoves();          // exit inner loop
                    }else if(game.wonGame()){  // if won
                         cout << endl << endl;
                         turn = game.getTurns() + 1;  //same to exit loops
                         game.clearMoves();
                    }else{  // if the game continues
                         system("clear");

                         // Board then player statuses and inventory is printed.
                         // Navigation panal is printed and input used to move player
                         // Loop continues and if the game isn't won we return here
                         // where the board is printed again with options.
                         game.printBoard();

                         cout << "Turn " << turn << ":" << endl;
                         game.playerStatus();
                         cout << endl << endl;

                         game.movePlayer(horizontalMenu("Pick Action... ", actions, 4));
                         game.playEvent();
                    }
               }
 
              
               // At the end of each turn the board state is printed again outside of the action
               // loop. Originally added just for testing but considered useful for a regular
               // end turn update.
               if(!(game.isDead()) && !(game.wonGame()))
               {
                    system("clear");

                    game.printBoard();
                    cout << endl << endl;

                    cout << "End of Turn " << turn << ":" << endl;
                    game.playerStatus();
                    cout << endl << endl;

                    pauseUntilInput();

                    // Unique to this section as the game continues.
                    // Movements are refreshed for the player and each space slowly replenishes
                    // its food. After 3 turns food++ until it reaches max capacity for that spot.
                    game.turnMaintenance();
          
                    turn++;
               }

          }


          // Turn incremembets in last section if no win conditions are met. Here if the
          // turns have exceeded the max then the losing statement is printed.
          if(turn > game.getTurns() && !(game.wonGame()) && !(game.isDead()))
          {
               system("clear");

               cout << "It looks like winter is coming and you're out of time to find home." << endl
                    << "I'm sure you'll get back to them next spring!" << endl << endl
                    << "GAME OVER" << endl << endl;
          }

          pauseUntilInput();

          system("clear");

          // Some condition has been met at this point and both middle and inner loops have
          // been exited. Asks the user to play again and validates a bool response.
          // If turn then outter loop iterates and a new board is generated to start over.
          cout << "Hope you enjoyed the Journey!" << endl
               << "Would you like to play again?" << endl;

          play = boolValidate();

     }

     // Outgoing message
     cout << endl << endl
          << "Thank you for playing..." << endl
          << "And thank you for this learning experience!" << endl << endl
          << "Have a good day." << endl << endl;
          

     

     return 0;
}
