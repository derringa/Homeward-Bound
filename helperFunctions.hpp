/**************************************************************************
 * File: General Helper Functions
 * Author: Andrew Derringer
 * Last Modified: 2/12/2019
**************************************************************************/

#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include <string>

using std::string;

int getRandomInteger(int, int);

double getRandomDouble(double, double);

int writeMenu(string, string*, int);

int horizontalMenu(string, string*, int);

bool runProgram(string, string);

bool runAgain(string);

void pauseUntilInput();

void arraySortAscend(int*, int);

int sortedArraySearch(int*, int, int);

int linearSearch(int*, int, int);

#endif
