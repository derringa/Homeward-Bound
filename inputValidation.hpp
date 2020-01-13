/***************************************
 * Program: InputValidations 
 * Author: Andrew Derriner
 * Last Modified: 2/10/2019
***************************************/

#ifndef INPUTVALIDATION_HPP
#define INPUTVALIDATION_HPP

#include <string>

using std::string;



int integerInputValidate();

int integerRangeValidate(string, int, int);

double doubleInputValidate();

double doubleRangeValidate(double, double);

bool boolValidate();

string continuousStringValidate(string);

char dpadValidation();
#endif
