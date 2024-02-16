#include "Room.h"
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

// Implementation of the randomlyTakeSeats method
void Room::randomlyTakeSeats(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin)
{
    vector<int> eventHours{ eventStartHour, eventStartMin, eventEndHour, eventEndMin }; // Creating a vector to access the seat matrix
    vector<vector<Seat>> seats = eventSeats[eventHours]; // Getting the seat matrix from the map

    srand(time(nullptr) + rngIteration * 2); // Generating a seed to avoid identical random results using rngIteration
    for (int row = 0; row < get_rows(); row++) // Looping through rows
    {
        for (int col = 0; col < get_columns(); col++) // Looping through columns
        {
            seats[row][col].set_isTaken(rand() % 2); // Randomly assigning seats as taken or not
        }
    }
    rngIteration = rngIteration + 1; // Increasing rngIteration

    eventSeats[eventHours] = seats; // Updating the seat vector in the map
}

// Implementation of the displaySeats method
void Room::displaySeats(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin)
{
    vector<int> eventHours{ eventStartHour, eventStartMin, eventEndHour, eventEndMin }; // Creating a vector to access the seat matrix
    vector<vector<Seat>>& seats = eventSeats[eventHours]; // Getting the seat matrix from the map

    cout << "    "; // Space in the upper-left corner

    for (int i = 1; i <= get_columns(); i++) // Printing column numbers
    {
        if (i < 10) { cout << i << "   "; }
        else { cout << i << "  "; }
    }

    for (int row = 0; row < get_rows(); row++) // Looping through rows
    {
        if (row + 1 < 10) { cout << endl << row + 1 << "  "; } // Printing row numbers
        else { cout << endl << row + 1 << " "; }

        for (int col = 0; col < get_columns(); col++) // Looping through columns
        {
            if (seats[row][col].get_isTaken() == 0)
            {
                cout << "[ ] "; // Printing empty seat
            }
            else
            {
                cout << "[X] "; // Printing taken seat
            }
        }
    }
}

// Implementation of the onlyRoomInfo method
void Room::onlyRoomInfo(bool displaySeats /*= true*/)
{
    string can3D;
    if (get_display3D() == true) { can3D = "2D/3D"; }
    else { can3D = "2D"; }
    cout << "\n          " << can3D << " ROOM number " << get_number() + 1 << "          " << "\n";
    if (displaySeats == false) { cout << "    Row: " << sRows << ",    Columns: " << sColumns << endl; }

    // If the user wants to see the seats matrix
    if (displaySeats == true)
    {
        cout << "    "; // Space in the upper-left corner
        for (int i = 1; i <= get_columns(); i++) // Printing column numbers
        {
            if (i < 10) { cout << i << "   "; }
            else { cout << i << "  "; }
        }

        for (int row = 0; row < get_rows(); row++) // Looping through rows
        {
            if (row + 1 < 10) { cout << endl << row + 1 << "  "; } // Printing row numbers
            else { cout << endl << row + 1 << " "; }

            for (int col = 0; col < get_columns(); col++) // Looping through columns
            {
                cout << "[ ] "; // Printing empty seat
            }
        }
    }
}

// Implementation of the info method
void Room::info(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin)
{
    string can3D;
    if (get_display3D() == true) { can3D = "2D/3D"; }
    else { can3D = "2D"; }
    cout << "\n          " << can3D << " ROOM number " << get_number() + 1 << "          " << "\n";
    displaySeats(eventStartHour, eventStartMin, eventEndHour, eventEndMin);
    cout << "\n\n";
}

// Implementation of the newSeatMatrix method
void Room::newSeatMatrix(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin)
{
    vector<int> eventHours{ eventStartHour, eventStartMin, eventEndHour, eventEndMin }; // Creating a vector to access the matrix

    vector<vector<Seat>> seats;
    seats.resize(sRows, vector<Seat>(sColumns)); // Creating the matrix of seat objects
    eventSeats.insert(make_pair(eventHours, seats)); // Assigning the matrix to the eventSeats map at the specified key
}

// Implementation of the deleteSeatMatrix method
void Room::deleteSeatMatrix(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin)
{
    vector<int> eventHours{ eventStartHour, eventStartMin, eventEndHour, eventEndMin }; // Creating a vector to access the matrix

    // Finding the iterator for the element with the key eventHours
    auto iterator = eventSeats.find(eventHours);

    // Checking if the element is found before deletion
    if (iterator != eventSeats.end())
    {
        // Deleting the element using the iterator
        eventSeats.erase(iterator);
    }
}

// Implementation of the changeSeatMatrixHours method
void Room::changeSeatMatrixHours(int oldEventStartHour, int oldEventStartMin, int oldEventEndHour, int oldEventEndMin,
    int newEventStartHour, int newEventStartMin, int newEventEndHour, int newEventEndMin)
{
    vector<int> oldEventHours{ oldEventStartHour, oldEventStartMin, oldEventEndHour, oldEventEndMin }; // Creating a vector to access the matrix we have created
    vector<vector<Seat>> seats = eventSeats[oldEventHours];

    deleteSeatMatrix(oldEventStartHour, oldEventStartMin, oldEventEndHour, oldEventEndMin);
    newSeatMatrix(newEventStartHour, newEventStartMin, newEventEndHour, newEventEndMin);

    vector<int> newEventHours{ newEventStartHour, newEventStartMin, newEventEndHour, newEventEndMin }; // Creating a vector to access the matrix we are deleting
    eventSeats[newEventHours] = seats;
}

// Implementation of the isSeatFree method
bool Room::isSeatFree(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin, int row, int column)
{
    vector<int> eventHours{ eventStartHour, eventStartMin, eventEndHour, eventEndMin }; // Creating a vector to access the matrix

    if (eventSeats[eventHours][row][column].get_isTaken() == true) { return false; }
    else if (eventSeats[eventHours][row][column].get_isTaken() == false) { return true; }
}

// Implementation of the takeSeat method
void Room::takeSeat(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin, int row, int column, string surname)
{
    vector<int> eventHours{ eventStartHour, eventStartMin, eventEndHour, eventEndMin }; // Creating a vector to access the matrix

    // Taking the seat
    eventSeats[eventHours][row][column].set_isTaken(true);
    eventSeats[eventHours][row][column].set_byWho(surname);
}

// Implementation of the freeSeat method
void Room::freeSeat(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin, int row, int column)
{
    vector<int> eventHours{ eventStartHour, eventStartMin, eventEndHour, eventEndMin }; // Creating a vector to access the matrix

    // Freeing the seat
    Seat defaultSeat;
    eventSeats[eventHours][row][column].set_isTaken(false);
    eventSeats[eventHours][row][column].set_byWho(defaultSeat.get_byWho());
}

// Implementation of the printOutEventSeats method
void Room::printOutEventSeats()
{
    cout << "\n******************";
    for (const auto& entry : eventSeats)
    {
        cout << "\nKey: ";
        for (int i = 0; i < entry.first.size();i++)
        {
            cout << entry.first[i] << ",";
        }
    }
}