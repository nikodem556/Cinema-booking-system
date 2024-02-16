#include "Day.h"

// Implementation of the getEventLength method
void Day::getEventLength(string eventName, int& eventStart, int& eventEnd,
    int searchStartHour, int searchStartMin, int searchStopHour, int searchStopMin)
{
    // Calculate the starting and stopping time in minutes
    int start = searchStartHour * 60 + searchStartMin;
    int end = searchStopHour * 60 + searchStopMin;
    eventStart = 0;

    // Find the starting minute of the specified event within the given time range
    for (int m = start; m < end; m++)
    {
        if (czas[m].get_byWhat() == eventName)
        {
            eventStart = m;
            break;
        }
    }

    // Find the ending minute of the specified event within the given time range
    for (int m = eventStart; m < end; m++)
    {
        if (czas[m].get_byWhat() != eventName)
        {
            eventEnd = m;
            break;
        }
    }
}

// Implementation of the findEventLength method
void Day::findEventLength(int searchStart, int searchStop)
{
    int m = searchStart;
    string eventName = czas[m].get_byWhat();
    int eventStart = 0;
    int eventEnd = searchStop;

    // Find the starting minute of the specified event within the given time range
    for (int k = m; k < searchStop; k++)
    {
        if (czas[k].get_byWhat() == eventName)
        {
            eventStart = k;
            break;
        }
    }

    // Find the ending minute of the specified event within the given time range
    for (int i = eventStart; i < searchStop; i++)
    {
        if (czas[i].get_byWhat() != czas[m].get_byWhat())
        {
            eventEnd = i;
            break;
        }
        else {}
    }

    // Convert the event start and end times to hours and minutes
    int eventStartHour = eventStart / 60;
    int eventStartMin = eventStart - eventStartHour * 60;
    int eventEndHour = eventEnd / 60;
    int eventEndMin = eventEnd - eventEndHour * 60;

    // Display the event information
    cout << "\n" << czas[m].get_byWhat() << ", ";
    if (eventStartMin < 10) { cout << eventStartHour << ":0" << eventStartMin << " - "; }
    else { cout << eventStartHour << ":" << eventStartMin << " - "; }
    if (eventEndMin < 10) { cout << eventEndHour << ":0" << eventEndMin << endl; }
    else { cout << eventEndHour << ":" << eventEndMin << endl; }
}

// Implementation of the setEvent method
bool Day::setEvent(string eventName, int startHour, int startMinute, int endHour, int endMinute, bool inform )
{
    // Display information about attempting to set the event
    if (inform == true)
    {
        cout << "\nTrying to set this event: " << eventName << ", ";
        preetyHours(startHour, startMinute, endHour, endMinute);
        // Opening the store, specifying the opening hours from 00 to the opening hour, and closing from closing to 24
    }

    // Calculate the starting and stopping time in minutes
    int start = startHour * 60 + startMinute;
    int end = endHour * 60 + endMinute;

    bool isFree = true; // Check if the time period is free along with the FOR loop
    for (int m = start; m < end; m++)
    {
        // If something is scheduled during this time, display information and return false
        if (czas[m].get_isUsed() == true)
        {
            // Display information about the conflicting event
            if (inform == true)
            {
                cout << "***ERROR: Another event is taking place during this period. Information below:";
                findEventLength(m);
            }

            isFree = false;

            // Display information about the inability to set the event
            if (inform == true)
            {
                cout << "***ERROR: Unable to set this event in this period. Try using another period or delete some events.***\n";
            }
            return false;
            break;
        }
    }

    // If the time period is free, set the event
    if (isFree == true)
    {
        eventNames.push_back(eventName);

        // Occupy the time slots with the event
        for (int m = start; m < end; m++)
        {
            czas[m].set_isUsed(true);
            czas[m].set_byWhat(eventName);
        }
        // Display success message
        if (inform == true)
        {
            cout << "Event was set." << endl;
        }
    }

    return true;
}

// Implementation of the deleteEvent method
void Day::deleteEvent(string eventName, int startHour, int startMinute, int endHour, int endMinute, bool inform)
{
    if (inform == true) { cout << "\nDeleting event: " << eventName << endl; }
    Minute minDefault;
    int start = startHour * 60 + startMinute;
    int end = endHour * 60 + endMinute;
    int eventStart = start; int eventEnd = end;

    // Retrieve the start and end minutes of the event
    getEventLength(eventName, eventStart, eventEnd, startHour, startMinute, endHour, endMinute);

    if (eventStart == 0 && eventEnd == 0)
    {
        if (inform == true)
        {
            cout << "***ERROR: Event wasn't found. Check if it's in the described time period.***" << endl;
        }
    }
    else
    {
        // Reset the minutes occupied by the event to default values
        for (int m = eventStart; m < eventEnd; m++)
        {
            czas[m].set_byWhat(minDefault.get_byWhat());
            czas[m].set_isUsed(minDefault.get_isUsed());
        }

        // Convert the event start and end times to hours and minutes
        int eventStartHour;
        int eventStartMin;
        int eventEndHour;
        int eventEndMin;

        minToPeriod(eventStart, eventEnd, eventStartHour, eventStartMin, eventEndHour, eventEndMin);

        // Remove the event name from the list of events
        for (int i = 0; i < eventNames.size(); i++)
        {
            if (eventNames[i] == eventName) { eventNames.erase(eventNames.begin() + i); break; }
        }

        if (inform == true)
        {
            // Display information about the deleted event
            cout << "Event has been found in: ";
            preetyHours(eventStartHour, eventStartMin, eventEndHour, eventEndMin, false);
            cout << " and was successfully deleted." << endl;
        }
    }
}

// Implementation of the changeEventHours method
void Day::changeEventHours(string eventName, int newStartHour, int newStartMinute, int newEndHour, int newEndMinute,
    int oldStartHour, int oldStartMinute, int oldEndHour, int oldEndMinute, bool inform)
{
    int eventStart, eventEnd;
    bool wasSuccessful;

    // Retrieve the start and end minutes of the event
    getEventLength(eventName, eventStart, eventEnd, oldStartHour, oldStartMinute, oldEndHour, oldEndMinute);

    // Assign precise duration of the event to existing variables
    minToPeriod(eventStart, eventEnd, oldStartHour, oldStartMinute, oldEndHour, oldEndMinute);

    if (inform == true)
    {
        // Display information about attempting to change event hours
        cout << "\nTrying to change event: \"" << eventName << "\" hours from ";
        preetyHours(oldStartHour, oldStartMinute, oldEndHour, oldEndMinute, false);
        cout << " to ";
        preetyHours(newStartHour, newStartMinute, newEndHour, newEndMinute);
    }

    // Set the event to new hours
    if (setEvent(eventName, newStartHour, newStartMinute, newEndHour, newEndMinute, false) == true)
    {
        // Delete the event
        deleteEvent(eventName, oldStartHour, oldStartMinute, oldEndHour, oldEndMinute, false);
        if (inform == true) { cout << "Event's hours were successfully changed." << endl; }
    }
    // If setting the new hours fails, nothing will change
}

// Implementation of the printOut method
void Day::printOut(int startHour, int startMin, int endHour, int endMin)
{
    cout << "\n***********************" << endl;
    cout << "\n" << "       " << "SCHEDULE" << "       " << endl;
    int start = startHour * 60 + startMin;
    int end = endHour * 60 + endMin;
    Minute defaultMin;

    for (int p = 0; p < eventNames.size(); p++)
    {
        for (int m = start; m < end; m++)
        {
            // If the minute is occupied, find the event and display information
            if (czas[m].get_byWhat() != defaultMin.get_byWhat())
            {
                int eventStart, eventEnd{};
                int searchStartHour = m / 60; int searchStartMin = m % 60;
                string eventName = czas[m].get_byWhat();
                getEventLength(eventName, eventStart, eventEnd, searchStartHour, searchStartMin);
                findEventLength(eventStart, eventEnd);
                start = eventStart + (eventEnd - eventStart);
                break;
            }
        }
    }
    cout << "\n\n***********************" << endl;
}

// Implementation of the reset method
void Day::reset(bool inform)
{
    Minute minDefault;
    // Reset all minutes to default values
    for (int m = 0; m < czas.size(); m++)
    {
        czas[m].set_byWhat(minDefault.get_byWhat());
        czas[m].set_isUsed(minDefault.get_isUsed());
    }
    if (inform == true)
    {
        // Display information about the reset
        cout << "\nEverything has been deleted" << endl;
    }
}