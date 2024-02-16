#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Time.h"

using namespace std;

class ValidityCheckFunctions
{
public:
	// check variable correctness in [startRange, stopRange] (in default informs if incorrect)
	bool isInRange(int startRange, int stopRange, int variable, bool inform = true);

	// check is variable a command (in vector commands) (in default informs if incorrect)
	bool isCommand(vector<string> commands, string variable, bool inform);

	// allow user to type in variable and if its an int - returns true (in default inform user if input is incorrect)
	bool isInputInt(int& inputVariable, bool inform = true);

};