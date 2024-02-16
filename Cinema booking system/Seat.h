#pragma once
#include <iostream>

using namespace std;

class Seat
{
private:
    bool fisTaken;   // Flag indicating whether the seat is taken
    string fbyWho;   // Name of the person who took the seat

public:

    // Default constructor with default parameters
    Seat(void) : fisTaken(false), fbyWho("Nobody") {}

    // Parameterized constructor
    Seat(bool isTaken, string byWho) : fisTaken(isTaken), fbyWho(byWho) {}

    // Getter methods
    bool get_isTaken(void) const { return fisTaken; }
    string get_byWho(void) const { return fbyWho; }

    // Setter methods
    void set_isTaken(bool change) { fisTaken = change; }
    void set_byWho(string someone) { fbyWho = someone; }

};
