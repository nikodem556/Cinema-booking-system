#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Minute.h"
#include "Time.h"

using namespace std;

class Day : private Time
{
private:
    vector<Minute> czas;    // Vector representing time - will have 1440 objects, corresponding to 24 hours
    vector<string> eventNames;   // Stores event names set using setEvent

public:

    // Remember that the elements in the vector will be up to 1439; czas[0] is 0:0, i.e., the 0th minute of the day, and 1439 is 23:59, the last minute of the day
    Day(void) { czas.resize(1440); } 

    // Getter
    vector<Minute> get_time(void) const { return czas; }

    // Outputs the duration of a specified event from minute searchStart to minute searchStop (default: end of the day)
    void findEventLength(int searchStart, int searchStop = 1440);

    // Retrieves the start and end minutes of an event within a specified time (default: entire day)
    void getEventLength(string eventName, int& eventStart, int& eventEnd,
        int searchStartHour = 0, int searchStartMin = 0, int searchStopHour = 24, int searchStopMin = 0);

    // Allows setting an event with the name 'eventName' at a specified time; inform displays text information
    bool setEvent(string eventName, int startHour, int startMinute, int endHour, int endMinute, bool inform = true);

    // Allows deleting an event with the name 'eventName' at a specified time (default: finds the earliest and deletes it entirely); inform displays text information
    void deleteEvent(string eventName, int startHour = 0, int startMinute = 0, int endHour = 24, int endMinute = 0, bool inform = true);

    /* Changes the hours of a given event; if there is only one event, there is no need to provide its start and end times -
        if there are multiple and we are not interested in the earliest, we need to provide them */
    void changeEventHours(string eventName, int newStartHour, int newStartMinute, int newEndHour, int newEndMinute,
        int oldStartHour = 0, int oldStartMinute = 0, int oldEndHour = 24, int oldEndMinute = 0, bool inform = true);

    // Displays the schedule for the specified time; without arguments - for the entire day
    void printOut(int startHour = 0, int startMin = 0, int endHour = 24, int endMin = 0);

    // Completely clears the schedule
    void reset(bool inform = true);
};

