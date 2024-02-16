#include "Order.h"

// Implementation of ticketInfo method
void Order::ticketInfo()
{
	// Displaying ticket information
	cout << "\n	  Client: " << fbyWho << endl << fday << ", ROOM " << froomNumber << ",	 SEAT: row " << frow + 1 << ", column " << fcolumn + 1;
	cout << "\n\"" << fmovieName << "\", ";
	preetyHours(fstartHour, fstartMin, fendHour, fendMin, false); cout << ", ";

	// Displaying movie details based on language and 3D options
	if (fPLdub == true && fis3D == true) { cout << "polish dubbing, 3D \n"; }
	else if (fPLdub == true && fis3D == false) { cout << "polish dubbing, 2D\n"; }
	else if (fPLdub == false && fis3D == true) { cout << "polish subtitles, 3D\n"; }
	else { cout << "polish subtitles, 2D\n"; }

	cout << "		CODE: " << fCode << endl;
}

// Implementation of buyTicket method
bool Order::buyTicket(Track& track, Room room, string day, int row, int column,
	Movie movie, int startHour, int startMin, int endHour, int endMin, bool wantPLdub, bool want3D, string userSurname, int userAge)
{
	cout << "\nTrying to buy ticket for movie \"" << movie.get_name() << "\".\n";
	int roomNumber = room.get_number();

	if ((checkIsTimeCorrect(startHour, startMin) && checkIsTimeCorrect(endHour, endMin)) == true) // if inputed time are correct
	{
		// checking if movie hours are correct
		int eventStart, eventEnd;
		track.get_roomTracks()[roomNumber].getEventLength(movie.get_name(), eventStart, eventEnd, startHour, startMin, endHour, endMin + 1);
		// there must be +1, because if there's not, getEventLength won't find its eventEnd
		// if the movie is in this period, new variables should be the same as the originals
		int sHour, sMin, eHour, eMin;
		minToPeriod(eventStart, eventEnd, sHour, sMin, eHour, eMin);  // assigning received minutes to new variables

		if ((startHour == sHour && startMin == sMin && endHour == eHour && endMin == eMin) == true) // if hours are correct
		{
			vector<int> movieHours{ startHour, startMin, endHour, endMin }; // we need this to get to seats matrix
			if (checkValidity(track, room, row, column, movie, movieHours, wantPLdub, want3D, userAge) == true)	// if user choices are correct
			{
				map <int, Room> rooms = track.get_rooms();
				rooms[roomNumber].takeSeat(startHour, startMin, endHour, endMin, row, column, userSurname); // taking seat

				// assigning changes to track
				track.set_rooms(rooms);

				froomNumber = room.get_number() + 1; fbyWho = userSurname; fmovieName = movie.get_name(); fday = day;
				fPLdub = wantPLdub; fis3D = want3D; frow = row; fcolumn = column;										// assigning variables to ticket
				fstartHour = startHour; fstartMin = startMin; fendHour = endHour; fendMin = endMin;
				cout << "Ticket was bought. Information below:\n";
				ticketInfo();
				return true;
			}
			else { return false; }
		}
		else
		{
			cout << "***ERROR: Invalid movie hours, try again with correct ones.***" << endl;
			return false;
		}
	}
	else { return false; }
}

// Implementation of checkValidity method
bool Order::checkValidity(Track track, Room room, int row, int column, Movie movie, vector<int> movieHours, bool wantPLdub, bool want3D, int userAge)
{
	if (room.get_rows() < row || room.get_columns() < column || row < 0 || column < 0)
	{
		cout << "\n***ERROR: Invalid row/column - that seat doesn't exist.***\n";
		return false;
	}
	if (userAge < movie.get_minAge()) // checking user age
	{
		cout << "\n***ERROR: You're too young to watch this movie, try another movie.***\n";
		return false;
	}

	if (wantPLdub == true)
	{
		if (movie.get_PLdub() == false) // if movie doesn't have PLdub
		{
			cout << "\n***ERROR: Movie doesn't have polish dubbing.***" << endl;
			return false;
		}
	}

	if (want3D == true)
	{
		if (room.get_display3D() == false) // if room doesn't support 3D
		{
			cout << "\n***ERROR: Room doesn't support 3D.***" << endl;
			return false;
		}
		if (movie.get_is3D() == false) // if movie doesn't have 3D version
		{
			cout << "\n***ERROR: This movie doesn't have a 3D version.***" << endl;
			return false;
		}
	}

	return true;
}