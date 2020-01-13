/**************************************************************************
 * File: General Helper Functions
 * Author: Andrew Derringer
 * Last Modified: 2/12/2019
 * Description: Includes random number generators for int and double, automated
 * menu writers,
**************************************************************************/

#include "helperFunctions.hpp"   // Receives <string>
#include "inputValidation.hpp"

#include <iostream>
#include <string>
#include <cstdlib> //for random number generator
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::max;



int getRandomInteger(int min, int max)   // In main "std::srand(std::time(0));"
{
	int randomInt = (rand() % (max - min + 1)) + min;
	return randomInt;
}



double getRandomDouble(double min, double max)   // In main "std::srand(std::time(0));"
{
	double randomDouble = ((double)rand() / (max - min + 1)) + min;
	return randomDouble;
}



int writeMenu(string menuTitle, string* stringArray, int arrayLength)
{
     cout << menuTitle << endl << endl
          << "------------------------------" << endl;

     for(int i = 0; i < arrayLength; i++)
     {
          cout << i + 1 << ") " << stringArray[i] << endl;
     }

     cout << "------------------------------" << endl
          << "Your choice:" << endl;

     int choice = integerRangeValidate(("Error: You must pick an integer between 1 and "
                  + std::to_string(arrayLength) + ". Try again:"), 1, arrayLength);

     return choice;
}



int horizontalMenu(string menuTitle, string* stringArray, int arrayLength)
{
     cout << menuTitle << endl
          << "---------------------------------------------------------------------|" << endl;

     for(int i = 0; i < arrayLength; i++)
     {
          cout << i + 1 << ") " << stringArray[i] << "     ";
     }

     cout << endl << "---------------------------------------------------------------------|" << endl
          << "Your choice: ";

     int choice = integerRangeValidate(("Error: You must pick an integer between 1 and "
                  + std::to_string(arrayLength) + ". Try again:"), 1, arrayLength);

     return choice;
}

bool runProgram(string title, string inquiry)
{
     cout << "|--------------------------------------------------|\n"
          << "|" + title + "|\n"
          << "|--------------------------------------------------|\n\n\n"

          << inquiry << endl;

     bool choice = boolValidate();

     return choice;
}



bool runAgain(string title)
{
     cout << "Would you like to run " + title + " again?" << endl;

     bool choice = boolValidate();

     return choice;
}



void pauseUntilInput()
{
     cout << "Press enter to continue." << endl;
     cin.clear();
     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
     cin.get();
}



/**************************************************************************
 * Passed: Array of integers and length of that array.
 * Returns:
 * Description: Uses selection sort method to sort integer array in
 * ascending order.
 * Citation: C++ Early Object 9th Edition Chapter 9.3
**************************************************************************/
void arraySortAscend(int* array, int length)
{
     // Outer loop holds index of the position to be evaluated and filled.
     // index 0 waits to receive lowest value, then next loop searches
     // from index 1 to end to find the lowest remaining value or second
     // lowest overall, etc until list is sorted.
     for(int selectionIndex = 0; selectionIndex < (length - 1); selectionIndex++)
     {
          int minValue = array[selectionIndex];
          int minIndex = selectionIndex;

          // iterates through array to find the lowest value.
          for(int searchIndex = selectionIndex + 1; searchIndex < length; searchIndex++)
          {
               if(array[searchIndex] < minValue)
               {
                    minValue = array[searchIndex];
                    minIndex = searchIndex;
               }
          }

          array[minIndex] = array[selectionIndex];
          array[selectionIndex] = minValue;
     }
}



/**************************************************************************
 * Passed: Array of integers, length of array, and value to be found.
 * Returns: interger of index position for value to be found.
 * Description: Only useful for sorted arrays! Ussesbinary search to
 * quickly break array into quadrants where the desired value might be.
 * Citation: C++ Early Objects 9th Edition Chapter 9.1
**************************************************************************/
int sortedArraySearch(int* array, int length, int searchValue)
{
     int first = 0;
     int last = length - 1;
     int middle;
     int position = -1;
     bool found = false;

     // Stops if value is found or first = last thus value not present
     while(!found && first <= last)
     {
          middle = (first + last) / 2;

          // if value = to middle then no need to keep searching quadrants.
          if(array[middle] == searchValue)
          {
               found = true;
               position = middle;
          // If middle value is greater than adjust search to first half of remaining search field.
          }else if(array[middle] > searchValue){
               last = middle - 1;
          // If middle value is less then adjust search to second half of remaining search field.
          }else{
               first = middle + 1;
          }
     }

     return position;
}



/**************************************************************************
 * Passed: Array of integers, length of array, and value to be found.
 * Returns: interger of index position for value to be found.
 * Description: Simple search iterates through entire list until it finds
 * the desired value or reaches the end.
 * Citation: C++ Early Objects 9th Edition Chapter 9.1
**************************************************************************/
int linearSearch(int* array, int length, int searchValue)
{
     bool found = false;
     int index = 0;
     int position = -1;

     while(index < length && !found)
     {
          if(array[index] == searchValue)
          {
               found = true;
               position = index;
          }
          index++;
     }

     return position;
}
