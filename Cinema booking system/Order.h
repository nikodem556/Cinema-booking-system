#pragma once
#include <iostream>
#include "Track.h"
#include "Room.h"
#include "User.h"
using namespace std;

class User;

class Order : private Time
{
	string fbyWho{}, fmovieName{};
	bool fPLdub{}, fis3D{};
	int frow{}, fcolumn{}, froomNumber{};
	int fstartHour{}, fstartMin{}, fendHour{}, fendMin{};
	string fday{};
	int fCode{};

	// Method to check the validity of buying a ticket with the specified parameters - doesn't verify isSeatFree
	bool checkValidity(Track track, Room room, int row, int column, Movie movie, vector<int> movieHours, bool wantPLdub, bool want3D, int userAge);

public:
	// Default constructor with initialization list
	Order(void) : fbyWho(""), fday("Friday"), fmovieName(""), fPLdub(false), fis3D(false), frow(0), fcolumn(0), froomNumber(0),
		fstartHour(0), fstartMin(0), fendHour(0), fendMin(0), fCode(0)
	{
		// Randomly generating ticketCode
		srand(time(NULL));
		fCode = (rand() % 9000) * 27 % 9000 + 1000;
	}

	// Getter for fCode
	int get_Code(void) const { return fCode; }

	// Getter for hours (contains startHour, startMin, endHour, endMin)
	vector<int> get_hours(void) const { return { fstartHour, fstartMin, fendHour, fendMin }; }

	// Getter for miscellaneous information (contains row, column, roomNumber, PLdub, is3D)
	vector<int> get_misc(void) const { return { frow, fcolumn, froomNumber, fPLdub, fis3D }; }

	// Getter for strings (contains movieName, day, byWho)
	vector<string> get_strings(void) const { return { fmovieName, fday, fbyWho }; }

	// Method to display ticket information
	void ticketInfo();

	// Method to buy a ticket with all the specified parameters
	bool buyTicket(Track& track, Room room, string day, int row, int column,
		Movie movie, int startHour, int startMin, int endHour, int endMin, bool wantPLdub, bool want3D, string userSurname, int userAge);
};

