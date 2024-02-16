#pragma once
#include <iostream>
#include <vector>
#include "Track.h"
#include "Room.h"
#include "Order.h"
#include "Movie.h"
using namespace std;

// We initialize class Order here, to be sure that it will initialize before User class
class Order;

// Class that can create User (cinema client) object and allow him to do buy/delete/show tickets
class User
{
private:
    string fsurname;    // User's surname
    int fage;           // User's age
    vector <Order> tickets;  // Vector to store User's purchased tickets

public:
    User(string surname, int age) : fsurname{ surname }, fage{ age } {}

    // Getters
    string get_surname(void) const { return fsurname; }
    int get_age(void) const { return fage; }

    // Method to buy a ticket and add it to the User's list of tickets
    void buyTicket(Track& track, Room room, string day, int row, int column,
        Movie movie, int startHour, int startMin, int endHour, int endMin, bool wantPLdub, bool want3D, string userSurname, int userAge);

    // Method to display all the tickets purchased by the User
    void showTickets();

    // Method to delete a ticket from the User's list and free up the corresponding seat in the cinema
    bool deleteTicket(vector<Track>& week, int ticketCode);
};
