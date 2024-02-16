#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "Seat.h"
#include <map>
using namespace std;

class Room
{
private:
	int fnumber, sRows, sColumns;
	bool fdisplay3D; // Can room display 3D
	map <vector<int>, vector<vector<Seat>>> eventSeats; // Key : vector<int> = {eventStartHour, eventStartMin, eventEndHour, eventEndMin}
	int rngIteration = 0; // counter for randomly generated seatsMatrix
public:
    // Default constructor with specified parameters
    Room(void) : fnumber(0), sRows(8), sColumns(8), fdisplay3D(false) {}

    // Parameterized constructor
    Room(int number, int rows, int columns, bool display3D) : fnumber{ number }, sRows{ rows }, sColumns{ columns }, fdisplay3D{ display3D } {}

    // Getters
    int get_number(void) const { return fnumber; }
    int get_rows(void) const { return sRows; }
    int get_columns(void) const { return sColumns; }
    bool get_display3D(void) const { return fdisplay3D; }
    map<vector<int>, vector<vector<Seat>>> get_eventSeats(void) const { return eventSeats; }

    // Setters
    void set_eventSeats(map<vector<int>, vector<vector<Seat>>> feventSeats) { eventSeats = feventSeats; }
    void set_number(int number) { fnumber = number; }
    void set_rows(int rows) { sRows = rows; }
    void set_columns(int columns) { sColumns = columns; }
    void set_display3D(bool canDisplay) { fdisplay3D = canDisplay; }

    // Function to randomly assign seats for an event
    void randomlyTakeSeats(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin);

    // Function to display the seats matrix for a specific event
    void displaySeats(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin);

    // Function to display only room information with empty seats matrix if desired
    void onlyRoomInfo(bool displaySeats = true);

    // Function to display room information along with the seats matrix for a specific event
    void info(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin);

    // Function to create a new seats matrix for an event
    void newSeatMatrix(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin);

    // Function to delete the seats matrix for a specific event
    void deleteSeatMatrix(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin);

    // Function to change the hours of a seats matrix from old to new hours
    void changeSeatMatrixHours(int oldEventStartHour, int oldEventStartMin, int oldEventEndHour, int oldEventEndMin,
        int newEventStartHour, int newEventStartMin, int newEventEndHour, int newEventEndMin);

    // Function to check if a seat is free in a seats matrix for a specific event
    bool isSeatFree(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin, int row, int column);

    // Function to reserve a seat in a seats matrix for a specific event
    void takeSeat(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin, int row, int column, string surname);

    // Function to free a reserved seat in a seats matrix for a specific event
    void freeSeat(int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin, int row, int column);

    // Function to print out event seats information
    void printOutEventSeats();
	
};

