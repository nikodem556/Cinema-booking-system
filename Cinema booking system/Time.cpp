#include "Time.h"

// Implementation of the checkIsTimeCorrect method
bool Time::checkIsTimeCorrect(int hour, int mins, bool inform /*= true*/)
{
    if (hour >= 0 && hour <= 23) // 1. whether the hour is in the range 0-23
    {
        if (mins >= 0 && mins <= 59) { return true; } // 2. whether the minutes are in the range 0-59, if yes, return true
        else { if (inform == true) { cout << "\n***ERROR: Introduced time values are incorrect.***\n"; } return false; } // 2. if not, return false
    }
    else if (hour == 24 && mins == 0) { return true; } // 1. if the hour is 24 but minutes are 0, allow it
    else
    {
        if (inform == true) { cout << "\n***ERROR: Introduced time values are incorrect.***\n"; }
        return false;  // 1. if not, return false
    }
}

// Implementation of the addTimes method
void Time::addTimes(int hour1, int min1, int hour2, int min2, int& sumHour, int& sumMin)
{
    if (checkIsTimeCorrect(hour1, min1, false) == true && checkIsTimeCorrect(hour2, min2, false) == true) // 0. check if the entered values are correct
    {
        if (hour1 + hour2 >= 24) // 1. if it goes beyond 23 hours:
        {
            sumHour = (hour1 + hour2) % 24;  // e.g., 27 hours becomes 3 AM

            if (min1 + min2 >= 60)	// 2. if it results in a full hour:
            {
                sumHour = sumHour + 1; // add one hour
                sumMin = (min1 + min2) % 60;

                if (sumHour == 24) { sumHour = 0; } // if it's 24, set it to 0
            }
            else { sumMin = min1 + min2; } // 2. if not, add minutes
        }
        else // 1. if it does not go beyond 24 hours
        {
            sumHour = hour1 + hour2;

            if (min1 + min2 >= 60)	// 2. if it results in more than a full hour:
            {
                sumHour = sumHour + 1; // add one hour
                sumMin = (min1 + min2) % 60;

                if (sumHour == 24) { sumHour = 0; } // if it's 24, set it to 0
            }
            else { sumMin = min1 + min2; } // 2. if not, add minutes
        }
    }
    else
    {
        sumHour = -1; sumMin = -1;
        cout << "\n***ERROR: Can't add values. Introduced time values are incorrect.***\n";
    }
}

// Implementation of the preetyHours method
void Time::preetyHours(int startHour, int startMin, int endHour, int endMin, bool endl /*= true*/)
{
    if (endl == true)
    {
        if (startMin < 10) { cout << startHour << ":0" << startMin << " - "; }
        else { cout << startHour << ":" << startMin << " - "; }

        if (endMin < 10) { cout << endHour << ":0" << endMin << "\n"; }
        else { cout << endHour << ":" << endMin << "\n"; }
    }
    else
    {
        if (startMin < 10) { cout << startHour << ":0" << startMin << " - "; }
        else { cout << startHour << ":" << startMin << " - "; }

        if (endMin < 10) { cout << endHour << ":0" << endMin; }
        else { cout << endHour << ":" << endMin; }
    }
}

// Implementation of the minToPeriod method
void Time::minToPeriod(int eventStart, int eventEnd, int& eventStartHour, int& eventStartMin, int& eventEndHour, int& eventEndMin)
{
    eventStartHour = eventStart / 60;
    eventStartMin = eventStart - eventStartHour * 60; // hours from the start to the end of this event
    eventEndHour = eventEnd / 60;
    eventEndMin = eventEnd - eventEndHour * 60;
}