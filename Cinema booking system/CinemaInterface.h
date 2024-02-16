#pragma once
#include <iostream>
#include <vector>
#include "Movie.h"
#include "Room.h"
#include <vector>
#include "Day.h"
#include "Track.h"
#include "User.h"
#include "Order.h"
#include "ValidityCheckFunctions.h"
#include "Time.h"
#include <cstdlib>

using namespace std;

class CinemaInterface : ValidityCheckFunctions, Time
{
private:
	vector <Movie> movies;
	vector <Room> rooms;
	vector<Track> week;
	vector<string> days{ "Monday", "Tuesday", "Wendesday", "Thursday", "Friday", "Saturday", "Sunday" };
	vector<User> users;

	// automatically and randomly sets day with movies (roomNumber is the number displayed in room's info)
	void regenerateRoom(int chooseDay, int roomNumber);

	// automatically and randomly sets day with movies
	void regenerateDay(int chooseDay);

	// automically and randomly sets all days with movies
	void regenerateWeek();

	// got a built-in empty track base that we use as day of the week (default open/closing hours are [13,23])
	void trackSetter();

	// loading every room to every track - necessary for schedule to not operate on default (constructor) rooms
	void loadRoomsIntoTracks();

	// if rooms weren't loaded in at least one track - return false (in default print ERROR)
	bool wereRoomsLoaded(bool inform = true);	

	// checks was tracks initialized, if not yet - return false (in default print ERROR)
	bool wereTracksInitialized(bool inform = true);

	// printing out all tracks with their openinig hours
	void printOutTracksHours();

	// got a built-in movie base that we use at the start of track Setter
	void movieSetter();

	// checks was movie initialized, if not yet - return false (in default print ERROR)
	bool wereMoviesInitialized(bool inform = true);

	// got a built-in room base that we use at the start of trackSetter
	void roomSetter();

	// checks was rooms initialized, if not yet - return false (in default print ERROR)
	bool wereRoomsInitialized(bool inform = true);

	// printsOut rooms basic info
	void showRooms();

	// search and print out movie playing hours in whole week's schedule
	vector<map<vector<int>, vector<int>>> searchMovieInWeek(Movie movie);	

	// menu text interface that printOut movies and (in default) allow to gather more information about them
	void menuShowMovies(bool additionalInfo = true, bool startText = true);
	
	// showing day's schedule (chooseDay is day's numeration in week, f.e Thursday = 4)
	void showDaySchedule(int chooseDay);

	// showing whole week schedule (in default it shows whole week at once, other option is to show one day at a time - after this user need to input a number to proceed)
	void showWeekSchedule(bool stepByStep = false);

	// menu text interface that shows whole week or chosen day's schedule
	void menuShowSchedule();

	// menu text interface that allows user to buyTicket
	bool menuBuyTicket(User& user);

	// menu text interface that shows user's tickets
	void menuShowTickets(User& user);

	// menu text interface that deletes user's ticket
	void menuDeleteTicket(User& user);	

	// menu text interface that shows when and where chosen movie is playing
	void menuWhenMovieIsPlaying();	

	// client main menu with text interface for client
	void clientMenu(User& user);	

	// menu text interface to add movies
	void menuAddMovie();
	
	// menu text interface to delete all movies or one's picked by user
	void menuDeleteMovie();
	
	// menu text interface to add rooms
	void menuAddRoom();

	// menu text option to delete all rooms or one's picked by user's
	void menuDeleteRoom();

	// menu text interface that resets day schedule
	void resetDaySchedule();

	// menu text interface that resets whole week schedule - in default informs user when it's done
	void resetWeekSchedule(bool inform = true);

	// menu text interface to manually add movie to the schedule
	void manuallyAddMovie();

	// menu text interface to manually delete movie from the schedule
	void manuallyDeleteMovie();

	// main menu for cinema manager with text interface
	void managerMenu();
	
public:

	// whole cinema interface
	void start();
};

