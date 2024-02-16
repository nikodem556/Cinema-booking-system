#include "ValidityCheckFunctions.h"

// Implementation of the isInRange method
bool ValidityCheckFunctions::isInRange(int startRange, int stopRange, int variable, bool inform)
{
	if (variable >= startRange && variable <= stopRange) { return true; }
	else
	{
		if (inform == true)
		{
			cout << "\n***ERROR: Invalid input. Try again.***" << endl;
		}
		return false;
	}
}

// Implementation of the isCommand method
bool ValidityCheckFunctions::isCommand(vector<string> commands, string variable, bool inform)
{
	for (int i = 0; i < commands.size(); i++)
	{
		if (variable == commands[i]) { return true; }
	}

	if (inform == true)
	{
		cout << "\n***ERROR: Invalid input. Try again.***" << endl;
	}
	return false;
}

// Implementation of the isInputInt method
bool ValidityCheckFunctions::isInputInt(int& inputVariable, bool inform)
{
	try
	{
		string input;
		cin >> input;

		int number = stoi(input); // Trying to convert input to int, if program can't do this...

		inputVariable = number; // if everything is alright
		return true;
	}
	catch (const invalid_argument& e)	// ...it catches this error and cout information
	{
		if (inform == true) { cerr << "\n***ERROR: Invalid input. Please enter integer.***" << endl; }
		return false;
	}
}