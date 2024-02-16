#pragma once
#include <iostream>
using namespace std;

class Minute
{
private:
	bool fisUsed;
	string fbyWhat;

public:
	// Default constructor
	Minute(void) : fisUsed(false), fbyWhat("nothing") {}

	// Parameterized constructor
	Minute(bool isUsed, string byWhat) : fisUsed{ isUsed }, fbyWhat{ byWhat } { }

	// Getter methods
	bool get_isUsed() const { return fisUsed; }
	string get_byWhat() const { return fbyWhat; }

	// Setter methods
	void set_isUsed(bool isUsed) { fisUsed = isUsed; }
	void set_byWhat(string byWhat) { fbyWhat = byWhat; }
};

