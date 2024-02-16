#pragma once
#include <iostream>
#include "ValidityCheckFunctions.h"

using namespace std;

// class which helps with mathematical operations on time and checks if values are correct
class Time
{
public:
	// function checks if the provided hours and minutes are correct
	bool checkIsTimeCorrect(int hour, int mins, bool inform = true);

	// function adds hours and minutes
	void addTimes(int hour1, int min1, int hour2, int min2, int& sumHour, int& sumMin);

	// prints the time nicely (defaults to adding endl at the end)
	void preetyHours(int startHour, int startMin, int endHour, int endMin, bool endl = true);

	// converts minute intervals to hours and minutes (extracting them by reference)
	void minToPeriod(int eventStart, int eventEnd, int& eventStartHour, int& eventStartMin, int& eventEndHour, int& eventEndMin);
};
