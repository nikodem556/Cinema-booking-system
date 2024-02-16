#include "CinemaInterface.h"
#include "ValidityCheckFunctions.h"

// Implementation of the regenerateRoom method
void CinemaInterface::regenerateRoom(int chooseDay, int roomNumber)
{
	// at first - resetting current room's schedule
	week[chooseDay - 1].resetRoomSchedule(week[chooseDay - 1].get_rooms()[roomNumber - 1], false);

	srand(time(NULL));

	int open = week[chooseDay - 1].get_openTime(); int closed = week[chooseDay - 1].get_closeTime();


	for (int m = open + 5; m < closed; m = m + 5) // setting movies in [open,closed] with 5min jump
	{
		if (m % 5 != 0) { int add = 5 - m % 5; m = m + add; }

		int startHour = m / 60;		int startMin = m % 60; // movie setting time
		int max = movies.size(); int draw = rand() % max; // drawing movie

		week[chooseDay - 1].setMovie(rooms[roomNumber - 1], movies[draw], startHour, startMin, false); // trying to set the movie
	}

}

// Implementation of the regenerateDay method
void CinemaInterface::regenerateDay(int chooseDay)
{
	// at first - resetting day's current schedule
	week[chooseDay - 1].resetTodaysSchedule(false);

	srand(time(NULL));

	int open = week[chooseDay - 1].get_openTime(); int closed = week[chooseDay - 1].get_closeTime();

	for (int r = 0; r < rooms.size(); r++) // going through each room
	{

		for (int m = open + 5; m < closed; m = m + 5) // setting movies in [open,closed] with 5min jump
		{
			if (m % 5 != 0) { int add = 5 - m % 5; m = m + add; }

			int startHour = m / 60;		int startMin = m % 60; // movie setting time
			int max = movies.size(); int draw = rand() % max; // drawing movie

			week[chooseDay - 1].setMovie(rooms[r], movies[draw], startHour, startMin, false); // trying to set the movie
		}
	}
}

// Implementation of the regenerateWeek method
void CinemaInterface::regenerateWeek()
{
	// resetting whole week schedule
	resetWeekSchedule(false);

	srand(time(NULL)); // seed draw

	// setting tracks with movies
	for (int t = 0; t < week.size(); t++) // going through each track
	{
		// getting when cinema is open in that day
		int open = week[t].get_openTime(); int closed = week[t].get_closeTime();

		for (int r = 0; r < rooms.size(); r++) // going through each room
		{

			for (int m = open + 5; m < closed; m = m + 5) // setting movies in [open,closed] with 5min jump
			{
				if (m % 5 != 0) { int add = 5 - m % 5; m = m + add; }

				int startHour = m / 60;		int startMin = m % 60; // movie setting time
				int max = movies.size(); int draw = rand() % max; // drawing movie

				week[t].setMovie(rooms[r], movies[draw], startHour, startMin, false); // trying to set the movie
			}
		}
	}
}

// Implementation of the trackSetter method
void CinemaInterface::trackSetter()
{
	int weeksSize = week.size();
	for (int i = weeksSize; i < 7; i++)
	{
		Track trackDay(13, 0, 23, 0);
		week.push_back(trackDay);
	}

}

// Implementation of the loadRoomsIntoTracks method
void CinemaInterface::loadRoomsIntoTracks()
{
	// adding every room to every track
	for (int t = 0; t < week.size(); t++)
	{
		for (int r = 0; r < rooms.size(); r++)
		{
			week[t].addRoom(rooms[r]);
		}
	}
}

// Implementation of the wereRoomsLoaded method
bool CinemaInterface::wereRoomsLoaded(bool inform)
{
	if (wereTracksInitialized(inform) == true)
	{
		for (int t = 0; t < week.size(); t++)
		{
			if (week[t].get_rooms().size() == 0)
			{
				if (inform == true) { cout << "\n***ERROR: Rooms weren't loaded into at least one track!***"; }
				return false;
			}
		}
		return true;
	}
	else
	{
		if (inform == true) { cout << "\n***ERROR: Initialize track before checking if rooms were loaded!***"; }
		return false;
	}
}

// Implementation of the wereTracksInitialized method
bool CinemaInterface::wereTracksInitialized(bool inform)
{
	// if there are no tracks yet - it breakes
	if (week.size() == 0)
	{
		if (inform == true) { cout << "\n***ERROR: There are no tracks initialized.***"; }
		return false;
	}

	else { return true; }
}

// Implementation of the printOutTracksHours method
void CinemaInterface::printOutTracksHours()
{
	cout << "\nCinema open hours:";
	for (int i = 0; i < week.size(); i++)
	{
		int openTime = week[i].get_openTime();
		int closeTime = week[i].get_closeTime();
		
		int openHour{}, openMin{}, closeHour{}, closeMin{};
		minToPeriod(openTime, closeTime, openHour, openMin, closeHour, closeMin);
		cout << "\n" << days[i] << ", "; preetyHours(openHour, openMin, closeHour, closeMin, false);
	}
}

// Implementation of the movieSetter method
void CinemaInterface::movieSetter()
{
	Movie megamocny("Megamind", "Animated", 1, 36, 9, true, true); movies.push_back(megamocny);
	Movie shrek("Shrek", "Animated", 1, 30, 7, true, true); movies.push_back(shrek);
	Movie avengers("Avengers: Endgame", "Action", 3, 1, 16, false, true); movies.push_back(avengers);
	Movie maverick("Top Gun: Maverick", "Action", 2, 11, 16, false, true); movies.push_back(maverick);
	Movie nun("The Nun 2", "Horror", 1, 40, 16, false, false); movies.push_back(nun);
	Movie it("It: Chapter Two", "Horror", 2, 49, 16, false, false); movies.push_back(it);
	Movie gump("Forrest Gump", "Comedy", 2, 21, 13, false, false); movies.push_back(gump);
	Movie inlaws("The In-Laws 2", "Comedy", 1, 35, 13, true, false); movies.push_back(inlaws);
}

// Implementation of the wereMoviesInitialized method
bool CinemaInterface::wereMoviesInitialized(bool inform)
{
	// if there are no movies yet - it breakes
	if (movies.size() == 0)
	{
		if (inform == true) { cout << "\n***ERROR: There are no movies initialized.***"; }
		return false;
	}

	else { return true; }
}

// Implementation of the roomSetter method
void CinemaInterface::roomSetter()
{
	Room r1big(0, 14, 16, true); rooms.push_back(r1big);
	Room r2med(1, 10, 12, false); rooms.push_back(r2med);
	Room r3med(2, 10, 10, true); rooms.push_back(r3med);
	Room r4sma(3, 7, 8, false); rooms.push_back(r4sma);
}

// Implementation of the wereRoomsInitialized method
bool CinemaInterface::wereRoomsInitialized(bool inform)
{
	// if there are no rooms yet - it breakes
	if (rooms.size() == 0)
	{
		if (inform == true) { cout << "\n***ERROR: There are no rooms initialized.***"; }
		return false;
	}

	else { return true; }
}

// Implementation of the showRooms method
void CinemaInterface::showRooms()
{
	for (int i = 0; i < rooms.size(); i++)
	{
		cout << endl;
		rooms[i].onlyRoomInfo();
	}
}

// Implementation of the searchMovieInWeek method
vector<map<vector<int>, vector<int>>> CinemaInterface::searchMovieInWeek(Movie movie)
{
	vector<map<vector<int>, vector<int>>> daySearchResult; // vector who will hold all the searching results

	int numberSearchedStart = 1; // we will start printing out from 1

	for (int i = 0; i < week.size(); i++)
	{
		cout << "\n		" << days[i] << ":\n";
		map<vector<int>, vector<int>> day = week[i].searchForMovie(movie, false, true, numberSearchedStart);

		// we need to check how many elements did it have to have continuity
		for (int k = 0; k < day.size(); k++)
		{
			numberSearchedStart = numberSearchedStart + 1;
		}

		// pushing back searchForMovie result
		daySearchResult.push_back(day);

	}

	return daySearchResult;
}

// Implementation of the menuShowMovies method
void CinemaInterface::menuShowMovies(bool additionalInfo, bool startText)
{
	if (startText == true) { cout << "\nWHAT ARE WE PLAYING RIGHT NOW:\n"; }
	// printing out movies
	for (int i = 0; i < movies.size(); i++)
	{
		cout << i + 1 << ".	\"" << movies[i].get_name() << "\"\n";
	}

	if (additionalInfo == true)
	{
		while (true)
		{

			cout << "\nType a number of movie that you would like to know more info: ";

			int chM{};
			// checking if chM is valid
			if (isInputInt(chM) == true) // if inputted value isInt
			{
				if (chM == -1) { break; } // if user typed -1 we exit 				
				else if (chM == 0) // reshowing movies list
				{
					cout << "\nWHAT ARE WE PLAYING RIGHT NOW:\n";
					// printing out movies
					for (int i = 0; i < movies.size(); i++)
					{
						cout << i + 1 << ".	\"" << movies[i].get_name() << "\"\n";
					}
				}
				else if (isInRange(1, movies.size(), chM) == true) { movies[chM - 1].info(); } // if inputted value isInRange we show movie info
			}
			cout << "\nIf you want to reshow movies list - input '0'.";
		}
	}
}

// Implementation of the showDaySchedule method
void CinemaInterface::showDaySchedule(int chooseDay)
{
	cout << "\n-------------------------";
	cout << "\n	 " << days[chooseDay - 1] << ":" << endl;
	week[chooseDay - 1].showTodaysSchedule(false);
}

// Implementation of the showWeekSchedule method
void CinemaInterface::showWeekSchedule(bool stepByStep)
{
	// we get whole week schedule by once
	if (stepByStep == false)
	{

		for (int day = 0; day < week.size(); day++)
		{
			cout << "\n-------------------------";
			cout << "\n	 " << days[day] << ":" << endl;
			week[day].showTodaysSchedule(false);
		}
	}

	// we show just one day, then we need to enter number to proceed to the next day
	else
	{

		for (int day = 0; day < week.size(); day++)
		{
			int passer{};
			cout << "\n-------------------------";
			cout << "\n	 " << days[day] << ":" << endl;
			week[day].showTodaysSchedule(false);

			// if we are at our last iteration of loop - we dont want user to input anything
			if (day != week.size() - 1)
			{
				// checking passer validity
				while (true)
				{
					cout << "Enter any number to proceed to " << days[day + 1] << "'s schedule: ";
					if (isInputInt(passer) == true) { break; }
				}
			}
		}

	}

}

// Implementation of the menuShowSchedule method
void CinemaInterface::menuShowSchedule()
{
	while (true) // 1. choosePeriod
	{

		cout << "\nIn which schedule are you interested in:\n1. Day\n2. Week\n";

		int choosePeriod{};
		// checking choosePeriod validity
		while (true)
		{
			cout << "Type your choice: ";

			if (isInputInt(choosePeriod) == true)
			{
				if (choosePeriod == -1) { break; } // user wants to exit
				else if (isInRange(1, 2, choosePeriod) == true) { break; }
			}
		}

		// user wants to exit
		if (choosePeriod == -1) { break; }

		// user chose Day
		else if (choosePeriod == 1)
		{
			while (true) // 2. chooseDay
			{

				for (int day = 0; day < week.size(); day++) // printing out avaiable days
				{
					cout << "\n" << day + 1 << ". " << days[day];
				}


				int chooseDay{};
				// checking chooseDay validity
				while (true) // 2a.
				{
					cout << "\nEnter number of day which schedule you want to see: ";
					if (isInputInt(chooseDay) == true)
					{
						if (chooseDay == -1) { break; } // we exit and go back to choosePeriod (1)
						else if (isInRange(1, week.size(), chooseDay) == true) { break; } // if inputted value isInRange
					}
				}

				// user wants to exit
				if (chooseDay == -1) { break; }

				// user chose a Day
				else
				{
					showDaySchedule(chooseDay);
				}

			} // while chooseDay(2)
		}

		// user chose Week
		else if (choosePeriod == 2)
		{
			cout << "\nHow do you want to display whole week schedule?\n1. At once\n2. One day at a time";
			cout << "\nType your choice: ";

			int chooseDisplay{};
			// checking chooseDisplay validity
			while (true)
			{
				if (isInputInt(chooseDisplay) == true)
				{
					if (chooseDisplay == -1) { break; } // user wants to exit to choosePeriod(1)
					else if (isInRange(1, 2, chooseDisplay) == true) { break; }
				}
			}

			// user wants to get week's schedule at once
			if (chooseDisplay == 1)
			{
				showWeekSchedule();
				break; // this allows us to exit choosePeriod(1) while
			}

			// user wants to get week's schedule day by day
			else if (chooseDisplay == 2)
			{
				showWeekSchedule(true);
				break; // this allows us to exit choosePeriod(1) while
			}
		}

	} // while choosePeriod (1)

}

// Implementation of the menuBuyTicket method
bool CinemaInterface::menuBuyTicket(User& user)
{
	while (true) // 1. choosePriority
	{
		bool goBackToChoosePriority = false; // we set this to false to allow user to enter chooseMovie (2)
		bool goBackToChooseMovie = false; // this will allow us to go back to chooseMovie(3) from chooseIteration if user types -1
		int choosePriority{};

		cout << "\nDo you want to buy a ticket for specific movie or day?\n1. Movie.\n2. Day.";
		// checking if choosePriority is valid
		while (true) // 1a.
		{
			cout << "\nType your choice: ";

			if (isInputInt(choosePriority) == true) // if inputted value isInt
			{
				if (choosePriority == -1) { return false; } // if user typed -1 we exit back to menu
				else if (isInRange(1, 2, choosePriority) == true) { break; } // if inputted value isInRange
			}
		}

		// user prioritizes Movie
		if (choosePriority == 1)
		{
			while (true) // 2. chooseMovie
			{
				if (goBackToChoosePriority == true) { break; } // if user type -1 in chooseMovie we go back to choosePriority (1)

				while (true) // 3. its for chooseIteration -1
				{
					cout << "\nIn which movie are you interested in?\n";

					// printing out movies
					for (int i = 0; i < movies.size(); i++)
					{
						cout << i + 1 << ".	\"" << movies[i].get_name() << "\"\n";
					}


					int chooseMovie{};
					// checking if chooseMovie is valid
					while (true) // 3a.
					{

						cout << "Select a movie. If you want to learn additional information about any movie - input ,0': ";
						if (isInputInt(chooseMovie) == true) // if inputted value isInt
						{
							if (chooseMovie == -1) { break; } // if user typed -1 we exit and go back to choosePriority (1)
							else if (isInRange(0, movies.size(), chooseMovie) == true) { break; } // if inputted value isInRange
						}
					}

					// if user types -1 in chooseMovie he goes back to choosePriority (1)
					if (chooseMovie == -1) { goBackToChoosePriority = true;break; }

					// user wants to know some more information
					else if (chooseMovie == 0)
					{
						while (true) // 3b.
						{
							cout << "\nType a number of movie that you would like to know more info, if you want to go back - input ,-1': ";

							int chM{};
							// checking if chM is valid
							if (isInputInt(chM) == true) // if inputted value isInt
							{
								if (isInRange(1, movies.size(), chM) == true) { movies[chM - 1].info(); } // if inputted value isInRange we show movie info
								else if (chM == -1) { break; } // if user typed -1 we exit and go back to chooseMovie (2)
							}
						}
					}

					// user has selected a movie
					else
					{

						while (true) // 4. chooseIteration
						{

							if (goBackToChooseMovie == true) { goBackToChooseMovie = false; break; } // allow us to go back to chooseMovie(2)

							while (true) // 4b. chooseIteration - its for Row and Column if -1
							{
								cout << "\nShowing when and where movie \"" << movies[chooseMovie - 1].get_name() << "\" is playing:\n";

								vector<map<vector<int>, vector<int>>> movieSearchInWeek;
								movieSearchInWeek = searchMovieInWeek(movies[chooseMovie - 1]); // printing out when and where

								int chooseIteration{};
								//checking chooseIteration validity
								while (true) // 4.
								{
									cout << "Now please choose when and where you want to watch the movie by entering number of movie iteration: ";
									if (isInputInt(chooseIteration) == true) // if inputted value isInt
									{
										// we get largest possibleIteration that user can input
										int maxIteration = 0;
										for (int day = 0; day < week.size(); day++)
										{
											// going through every map element in current week day
											for (const auto& entry : movieSearchInWeek[day])
											{
												maxIteration = maxIteration + 1;
											}
										}
										if (chooseIteration == -1) { break; } // if user typed -1 we exit and go back to chooseMovie (2)
										else if (isInRange(1, maxIteration, chooseIteration) == true) { break; } // if inputted value isInRange
									}
								}

								if (chooseIteration == -1) { goBackToChooseMovie = true; break; } // if user typed -1 we exit and go back to chooseMovie(3)

								// user has selected an iteration
								else
								{
									// we will use iteration to find user chooseIteration and get info needed to buy him ticket
									int iteration = 1;
									int roomNumber{};
									int movieStartHour{};
									int movieStartMin{};
									int movieEndHour{};
									int movieEndMin{};
									int pickedDay{};

									// searching user chooseIteration, firstly accesing every week day
									for (int day = 0; day < week.size(); day++)
									{
										// going through every map element in current week day
										for (const auto& entry : movieSearchInWeek[day])
										{
											// if we find our user chooseIteration
											if (chooseIteration == iteration)
											{
												roomNumber = entry.first[0]; // getting chooseIteration roomNumber
												movieStartHour = entry.second[0];
												movieStartMin = entry.second[1];
												movieEndHour = entry.second[2];
												movieEndMin = entry.second[3];
												pickedDay = day;
											}

											iteration = iteration + 1;
										}
									}

									// printing out user choice
									cout << "\nYour choice is: " << days[pickedDay] << ", Room " << roomNumber + 1 << ", ";
									preetyHours(movieStartHour, movieStartMin, movieEndHour, movieEndMin, false);

									cout << "\nNow please choose your seat, the ones with [X] are already occupied\n\n";

									week[pickedDay].get_rooms()[roomNumber].displaySeats(movieStartHour, movieStartMin, movieEndHour, movieEndMin); // displaying seat Matrix

									bool goBackToChooseIteration = false;

									while (true) // 5. chooseRow and chooseColumn, this loops allow us to dont go back if user seats taken
									{

										if (goBackToChooseIteration == true) { break; }

										int chooseRow{};
										// checking chooseRow validity
										while (true) // 5a.
										{
											cout << "\nRow: ";
											if (isInputInt(chooseRow) == true) // if inputted value isInt
											{
												if (chooseRow == -1) { break; }
												else if (isInRange(1, week[pickedDay].get_rooms()[roomNumber].get_rows(), chooseRow) == true) { break; } // if inputted value isInRange
											}
										}

										if (chooseRow == -1) { goBackToChooseIteration = true; break; }
										// tutaj trzeba zrobic ze po wpisaniu -1 sie cofamy do wyboru iteracji

										int chooseColumn{};
										// checking chooseColumn validity
										while (true) // 5b.
										{
											cout << "Column: ";
											if (isInputInt(chooseColumn) == true) // if inputted value isInt
											{
												if (chooseColumn == -1) { break; }
												else if (isInRange(1, week[pickedDay].get_rooms()[roomNumber].get_columns(), chooseColumn) == true) { break; } // if inputted value isInRange
											}
										}

										if (chooseColumn == -1) { goBackToChooseIteration = true; break; }

										// checking isSeatFree
										if (week[pickedDay].get_rooms()[roomNumber].isSeatFree(movieStartHour, movieStartMin, movieEndHour, movieEndMin, chooseRow - 1, chooseColumn - 1) == false)
										{
											cout << "***ERROR: This seat is taken. Please try another seat.***";
										}


										// if seat is free
										else
										{
											user.buyTicket(week[pickedDay], rooms[roomNumber], days[pickedDay], chooseRow - 1, chooseColumn - 1, movies[chooseMovie - 1],
												movieStartHour, movieStartMin, movieEndHour, movieEndMin, false, false, user.get_surname(), user.get_age());

											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		// if user prioritizes day
		else if (choosePriority == 2)
		{
			while (true) // 2. chooseDay
			{
				//bool goBackToChooseDay = false;

				cout << "\nDays when cinema is open:";
				for (int day = 0; day < week.size(); day++) // printing out avaiable days
				{
					cout << "\n" << day + 1 << ". " << days[day];
				}


				int chooseDay{};
				// checking chooseDay validity
				while (true) // 2a.
				{
					cout << "\nEnter number of day which schedule you want to see: ";
					if (isInputInt(chooseDay) == true)
					{
						if (chooseDay == -1) { break; } // we exit and go back to choosePriority (1)
						else if (isInRange(1, week.size(), chooseDay) == true) { break; } // if inputted value isInRange
					}
				}

				if (chooseDay == -1) { break; } // we go back to choosePriority(1)

				else
				{
					cout << "\nYou have picked " << days[chooseDay - 1] << ".";
					week[chooseDay - 1].showTodaysSchedule(); // showing day's schedule

					int chooseMovie{};
					while (true) // 3. chooseMovie
					{
						goBackToChooseMovie = false;

						cout << "\nDecide what and when you want to watch. To proceed with selecting your chosen movie's number from list below.";
						cout << "\nFor reshow of day's schedule input ,-2'. If you want to learn additional information about any movie - input ,0'.";
						cout << endl;
						for (int i = 0; i < movies.size(); i++)
						{
							cout << i + 1 << ".	\"" << movies[i].get_name() << "\"\n";
						}

						while (true) // 3a.
						{

							cout << "Select a movie: ";
							if (isInputInt(chooseMovie) == true) // if inputted value isInt
							{
								if (chooseMovie == -1) { break; } // if user typed -1 we exit and go back to chooseDay (2)
								else if (chooseMovie == -2) { break; } // if user typed -2 we reshow this day schedule
								else if (isInRange(0, movies.size(), chooseMovie) == true) { break; } // if inputted value isInRange
							}
						}

						// if user types -1 in chooseMovie he goes back to chooseDay (2)
						if (chooseMovie == -1) { /*goBackToChooseDay = true;*/ break; }

						// if user wants to reshow schedule
						else if (chooseMovie == -2) { cout << "\nReshowing " << days[chooseDay - 1] << " schedule"; week[chooseDay - 1].showTodaysSchedule(); }

						// user wants to know some more information
						else if (chooseMovie == 0)
						{
							while (true) // 3b.
							{
								cout << "\nType a number of movie that you would like to know more info, if you want to go back - input ,-1': ";

								int chM{};
								// checking if chM is valid
								if (isInputInt(chM) == true) // if inputted value isInt
								{
									if (isInRange(1, movies.size(), chM) == true) { movies[chM - 1].info(); } // if inputted value isInRange we show movie info
									else if (chM == -1) { break; } // if user typed -1 we exit and go back to chooseMovie (3)
								}
							}
						}

						// user picked a movie
						else
						{

							while (true) // 4. chooseIteration
							{

								if (goBackToChooseMovie == true) { goBackToChooseMovie = false; break; } // allow us to go back to chooseMovie(3)

								while (true) // 4b. chooseIteration - its for Row and Column if -1
								{
									cout << "\nShowing when and where movie \"" << movies[chooseMovie - 1].get_name() << "\" is playing:\n";

									map<vector<int>, vector<int>> movieSearchInDay;
									movieSearchInDay = week[chooseDay - 1].searchForMovie(movies[chooseMovie - 1], true, true); // printing out when and where

									// wypisywanie zawartosci movieSearchInWeek
									/*int printOutIteration = 1;
									for (int day = 0; day < week.size(); day++)
									{
										cout << "\n\n" << days[day] << ":";
										for (const auto& entry : movieSearchInWeek[day])
										{
											cout << "\n" << printOutIteration << ". ";
											printOutIteration = printOutIteration + 1;
											cout << "Key: ";
											for (int i = 0; i < entry.first.size(); i++)
											{
												cout << entry.first[i] << ", ";
											}

											cout << "\nValue: ";
											for (int i = 0; i < entry.second.size(); i++)
											{
												cout << entry.second[i] << ", ";
											}
										}
									}*/

									int chooseIteration{};
									//checking chooseIteration validity
									while (true) // 4.
									{
										cout << "Now please choose when and where you want to watch the movie by entering number of movie iteration: ";
										if (isInputInt(chooseIteration) == true) // if inputted value isInt
										{
											if (chooseIteration == -1) { break; } // if user typed -1 we exit and go back to chooseMovie (2)
											else if (isInRange(1, movieSearchInDay.size(), chooseIteration) == true) { break; } // if inputted value isInRange
										}
									}

									if (chooseIteration == -1) { goBackToChooseMovie = true; break; } // if user typed -1 we exit and go back to chooseMovie(3)

									// user has selected an iteration
									else
									{
										// we will use iteration to find user chooseIteration and get info needed to buy him ticket
										int iteration = 1;
										int roomNumber{};
										int movieStartHour{};
										int movieStartMin{};
										int movieEndHour{};
										int movieEndMin{};


										// going through every map element in user chosen week day
										for (const auto& entry : movieSearchInDay)
										{
											// if we find our user chooseIteration
											if (chooseIteration == iteration)
											{
												roomNumber = entry.first[0]; // getting chooseIteration roomNumber
												movieStartHour = entry.second[0];
												movieStartMin = entry.second[1];
												movieEndHour = entry.second[2];
												movieEndMin = entry.second[3];
											}

											iteration = iteration + 1;
										}


										// printing out user choice
										cout << "\nYour choice is: " << days[chooseDay - 1] << ", Room " << roomNumber + 1 << ", ";
										preetyHours(movieStartHour, movieStartMin, movieEndHour, movieEndMin, false);

										cout << "\nNow please choose your seat, the ones with [X] are already occupied\n\n";

										week[chooseDay - 1].get_rooms()[roomNumber].displaySeats(movieStartHour, movieStartMin, movieEndHour, movieEndMin); // displaying seat Matrix

										bool goBackToChooseIteration = false;

										while (true) // 5. chooseRow and chooseColumn, this loops allow us to dont go back if user seats taken
										{

											if (goBackToChooseIteration == true) { break; }

											int chooseRow{};
											// checking chooseRow validity
											while (true) // 5a.
											{
												cout << "\nRow: ";
												if (isInputInt(chooseRow) == true) // if inputted value isInt
												{
													if (chooseRow == -1) { break; }
													else if (isInRange(1, week[chooseDay - 1].get_rooms()[roomNumber].get_rows(), chooseRow) == true) { break; } // if inputted value isInRange
												}
											}

											if (chooseRow == -1) { goBackToChooseIteration = true; break; }
											// tutaj trzeba zrobic ze po wpisaniu -1 sie cofamy do wyboru iteracji

											int chooseColumn{};
											// checking chooseColumn validity
											while (true) // 5b.
											{
												cout << "Column: ";
												if (isInputInt(chooseColumn) == true) // if inputted value isInt
												{
													if (chooseColumn == -1) { break; }
													else if (isInRange(1, week[chooseDay - 1].get_rooms()[roomNumber].get_columns(), chooseColumn) == true) { break; } // if inputted value isInRange
												}
											}

											if (chooseColumn == -1) { goBackToChooseIteration = true; break; }

											// testy
											/*week[pickedDay].get_rooms()[roomNumber].onlyRoomInfo();
											for (int k = 0; k < chooseRow; k++)
											{
												for (int i = 0; i < chooseColumn; i++)
												{
													cout << i << ", row:" << k << " is free: " << week[pickedDay].get_rooms()[roomNumber].isSeatFree(movieStartHour, movieStartMin, movieEndHour, movieEndMin, k, i) << endl;
												}
											}
											week[pickedDay].get_rooms()[roomNumber].onlyRoomInfo();*/

											// checking isSeatFree
											if (week[chooseDay - 1].get_rooms()[roomNumber].isSeatFree(movieStartHour, movieStartMin, movieEndHour, movieEndMin, chooseRow - 1, chooseColumn - 1) == false)
											{
												cout << "This seat is taken. Please try another seat.";
											}


											// if seat is free
											else
											{
												// zmien tutaj z tym dubbingiem i 3D; albo jak jest dubbing to zawsze jest dubbing albo trzeba losowac, jak jest 3d film to zawsze 3d
												user.buyTicket(week[chooseDay - 1], rooms[roomNumber], days[chooseDay - 1], chooseRow - 1, chooseColumn - 1, movies[chooseMovie - 1],
													movieStartHour, movieStartMin, movieEndHour, movieEndMin, false, false, user.get_surname(), user.get_age());
												//week[pickedDay].get_rooms()[roomNumber].takeSeat(movieStartHour, movieStartMin, movieEndHour, movieEndMin, chooseRow - 1, chooseColumn - 1, user.get_surname());
												//week[pickedDay].get_rooms()[roomNumber].get_eventSeats()[{movieStartHour, movieStartMin, movieEndHour, movieEndMin}][chooseRow - 1][chooseColumn - 1].tookplace();
												//week[pickedDay].get_rooms()[roomNumber].displaySeats(movieStartHour, movieStartMin, movieEndHour, movieEndMin); // displaying seat Matrix
												//cout << "\nisfree:" << week[pickedDay].get_rooms()[roomNumber].isSeatFree(movieStartHour, movieStartMin, movieEndHour, movieEndMin, chooseRow - 1, chooseColumn - 1);

												return true;
											}
										}
									}
								}
							}
						}


					}

				}
			}



		}
	}
}

// Implementation of the menuShowTickets method
void CinemaInterface::menuShowTickets(User& user)
{
	user.showTickets();

	int number{};
	// checking chooseCom validity
	while (true)
	{
		cout << "\nEnter any number to proceed: ";

		if (isInputInt(number) == true) { break; }
	}
}

// Implementation of the menuDeleteTicket method
void CinemaInterface::menuDeleteTicket(User& user)
{
	while (true)
	{
		int ticketCode{};
		// checking ticketCode validity
		while (true)
		{
			cout << "\nEnter ticket's CODE which you want to delete. If you want to show your tickets - input '0'.";
			cout << "\nTicket's CODE should be written at the bottom of the ticket: ";
			if (isInputInt(ticketCode) == true)
			{
				if (ticketCode == -1) { break; }
				else if (ticketCode == 0) { user.showTickets(); }
				else if (isInRange(1000, 9999, ticketCode) == true) { break; }
			}
		}

		// if user wants to exit
		if (ticketCode == -1) { break; }

		// user wants to delete ticket
		else
		{
			// valid ticketCode 
			if (user.deleteTicket(week, ticketCode) == true) { break; }

			// invalid ticketCode
			else {}
		}
	}
}

// Implementation of the menuWhenMovieIsPlaying method
void CinemaInterface::menuWhenMovieIsPlaying()
{
	bool exitNow = false;
	while (true) // 1. choosePeriod
	{
		if (exitNow == true) { break; } // this allows us to exit immediately

		cout << "\nYou can view when and where movie is playing in:\n1. Day\n2. Week\n";

		int choosePeriod{};
		// checking choosePeriod validity
		while (true)
		{
			cout << "Type your choice: ";

			if (isInputInt(choosePeriod) == true)
			{
				if (isInRange(1, 2, choosePeriod) == true) { break; }
				else if (choosePeriod == -1) { break; } // user wants to exit
			}
		}

		// user wants to exit
		if (choosePeriod == -1) { break; }

		// user chose Day
		else if (choosePeriod == 1)
		{
			while (true) // 2. chooseDay
			{

				if (exitNow == true) { break; } // this allows us to exit immediately

				cout << "\nDays when cinema is open:";
				for (int day = 0; day < week.size(); day++) // printing out avaiable days
				{
					cout << "\n" << day + 1 << ". " << days[day];
				}


				int chooseDay{};
				// checking chooseDay validity
				while (true) // 2a.
				{
					cout << "\nEnter number of day which schedule you want to see: ";
					if (isInputInt(chooseDay) == true)
					{
						if (chooseDay == -1) { break; } // we exit and go back to choosePeriod (1)
						else if (isInRange(1, week.size(), chooseDay) == true) { break; } // if inputted value isInRange
					}
				}

				if (chooseDay == -1) { break; } // we go back to choosePeriod(1)

				else
				{
					cout << "\nYou have picked " << days[chooseDay - 1] << ".\n";

					bool goBackToChooseDay = false; // that bool will allow us to exit with -1 from 4. scheduleLoop
					int chooseMovie{};
					while (true) // 3. chooseMovie
					{
						if (goBackToChooseDay == true) { break; } // this allows us to goBackToChooseDay
						if (exitNow == true) { break; } // this allows us to exit immediately

						menuShowMovies(false, true);

						while (true) // 4. scheduleLoop - user will be looped here after chosing movie, unless he put valid input to exit
						{


							while (true) // 4a.
							{

								cout << "If you want to exit immediately - input '0'. To reshow movies list - input '-2'.\nSelect a movie: ";
								if (isInputInt(chooseMovie) == true) // if inputted value isInt
								{
									if (chooseMovie == -1) { break; } // if user typed -1 we exit and go back to chooseDay (2)
									else if (chooseMovie == -2) { break; } // user wants to reshow movies list
									else if (chooseMovie == 0) { break; } // if user wants to exit immadietely
									else if (isInRange(1, movies.size(), chooseMovie) == true) { break; } // if inputted value isInRange
								}
							}

							// if user types 0 in chooseMovie he goes back to menu
							if (chooseMovie == 0) { exitNow = true; break; }

							// if user types -1 in chooseMovie he goes back to chooseDay (2)
							if (chooseMovie == -1) { goBackToChooseDay = true; break; }

							// reshowing movies list
							else if (chooseMovie == -2)
							{
								cout << endl;
								menuShowMovies(false, false);
							}

							// user picked a movie
							else
							{
								week[chooseDay - 1].searchForMovie(movies[chooseMovie - 1], true, true); // printing out when and where
							}
						} // 4. scheduleLoop while
					} // 3. chooseMovie while
				}
			} // 2. chooseDay while

		} // user chose Day

		// user chose Week
		else if (choosePeriod == 2)
		{

			menuShowMovies(false, true);

			while (true) // 2. chooseMovie
			{

				if (exitNow == true) { break; } // this allows us to exit immediately

				int chooseMovie{};
				// checking chooseMovie validity
				while (true)
				{
					cout << "If you want to exit immediately - input '0'. To reshow movies list - input '-2'.\nSelect a movie: ";
					if (isInputInt(chooseMovie) == true) // if inputted value isInt
					{
						if (chooseMovie == -1) { break; } // if user typed -1 we exit and go back to choosePeriod (1)
						else if (chooseMovie == 0) { break; } // if user wants to exit immadietely
						else if (chooseMovie == -2) { break; } // user wants to reshow movies list
						else if (isInRange(1, movies.size(), chooseMovie) == true) { break; } // if inputted value isInRange
					}
				}

				// if user types 0 in chooseMovie he goes back to menu
				if (chooseMovie == 0) { exitNow = true; break; }

				// if user types -1 in chooseMovie he goes back to choosePeriod (1)
				if (chooseMovie == -1) { break; }

				// reshowing movies list
				else if (chooseMovie == -2)
				{
					cout << endl;
					menuShowMovies(false, false);
				}

				// user picked a movie
				else
				{
					cout << "\nShowing when and where movie \"" << movies[chooseMovie - 1].get_name() << "\" is playing:\n";

					searchMovieInWeek(movies[chooseMovie - 1]); // printing out when and where
				}
			} // while chooseMovie

		} // user chose Week


	} // 1. choosePeriod while
}

// Implementation of the clientMenu method
void CinemaInterface::clientMenu(User& user)
{
	while (true)
	{
		cout << "\n**************************MAIN MENU***********************************";
		cout << "\nHey " << user.get_surname() << "! "; cout << "This is main menu. Remember that you can ALWAYS go back by inputing '-1'.\n";
		cout << "\nAVAIABLE COMMANDS:";
		cout << "\n1. Buy ticket for a movie.";
		cout << "\n2. Show your tickets.";
		cout << "\n3. Cancel your ticket.";
		cout << "\n4. Show movies in play.";
		cout << "\n5. Show when and where movie is playing.";
		cout << "\n6. Show week/day schedule.";
		cout << "\n7. Clear console window.";
		cout << endl;


		int chooseCom{}; // shortcut for chooseCommand
		// checking chooseCom validity
		while (true)
		{
			cout << "\nChoose what you want to do by writing number: ";

			if (isInputInt(chooseCom) == true) // if inputted value isInt
			{
				if (chooseCom == -1) { break; } // user wants to exit
				else if (isInRange(1, 7, chooseCom) == true) { break; } // if inputted value isInRange
			}
		}

		// user wants to exit
		if (chooseCom == -1) { break; }

		// user wants to buy a ticket
		else if (chooseCom == 1)
		{
			menuBuyTicket(user);
		}

		// showing user's tickets
		else if (chooseCom == 2)
		{
			menuShowTickets(user);
		}

		// deleting user's ticket
		else if (chooseCom == 3)
		{
			menuDeleteTicket(user);
		}

		// showing movies in play
		else if (chooseCom == 4)
		{
			menuShowMovies();
		}

		// searching movie in week/day
		else if (chooseCom == 5)
		{
			menuWhenMovieIsPlaying();
		}

		// showing week/day schedule
		else if (chooseCom == 6)
		{
			menuShowSchedule();
		}

		// user wants to clear console window
		else if (chooseCom == 7)
		{
			system("cls");
		}

	} // MAIN MENU WHILE
}

// Implementation of the menuAddMovie method
void CinemaInterface::menuAddMovie()
{
	while (true) // 2. addMovie
	{
		cout << "\nBe careful with your inputs - inputting ,-1, wont take you back to last movie parameter, but to previous menu.";

		string mName{}; // inputting movie's name
		cout << "\nEnter movie's name: "; cin >> ws;  getline(cin, mName);

		string mGenre{}; // inputting movie's genre
		cout << "\nEnter movie's genre: "; cin >> ws;  getline(cin, mGenre);

		int mHours{}; // inputting movie's length in hours
		int mMins{}; // inputting movie's length in minutes
		// checking movie's length validity
		while (true)
		{

			while (true) // checking if mHours is integer
			{
				cout << "\nHow many hours does movie take?: ";
				if (isInputInt(mHours) == true) { break; }
			}

			if (mHours == -1) { break; } // user wants to exit

			while (true) // checking if mMins is integer
			{
				cout << "\nHow many minutes does movie take?: ";
				if (isInputInt(mMins) == true) { break; }
			}

			// if inputted values are correct - we can proceed
			if (mMins == -1) { break; }
			else if (checkIsTimeCorrect(mHours, mMins) == true) { break; }
		}

		// user wants to exit
		if (mHours == -1 || mMins == -1) { break; }

		int mMinAge{}; // inputting movie's minAge
		// checking minAge validity
		while (true)
		{
			cout << "\nEnter minimum age required to watch the movie: ";
			if (isInputInt(mMinAge) == true)
			{
				if (mMinAge == -1) { break; }
				else if (isInRange(6, 18, mMinAge) == true) { break; }
			}
		}

		// user wants to exit
		if (mMinAge == -1) { break; }

		int choosePLDub{}; // does movie has PL dub
		cout << "\nDoes your movie has PL dubbing?:\n1. Yes.\n2. No.";
		// checking choosePLdub validity
		while (true)
		{
			cout << "\nType your answer: ";
			if (isInputInt(choosePLDub) == true) // if inputted value isInt
			{
				if (choosePLDub == -1) { break; } // user wants to exit
				else if (isInRange(1, 2, choosePLDub) == true) { break; } // if inputted value isInRange
			}
		}

		bool hasPLDub{};

		// user wants to exit
		if (choosePLDub == -1) { break; }

		// movie has PL dub
		else if (choosePLDub == 1) { hasPLDub = true; }

		// movie hasn't got PL dub
		else if (choosePLDub == 2) { hasPLDub = false; }


		int choose3D{}; // does movie has 3D
		cout << "\nDoes your movie has 3D?:\n1. Yes.\n2. No.";
		// checking choose3D validity
		while (true)
		{
			cout << "\nType your answer: ";
			if (isInputInt(choose3D) == true) // if inputted value isInt
			{
				if (choose3D == -1) { break; } // user wants to exit
				else if (isInRange(1, 2, choose3D) == true) { break; } // if inputted value isInRange
			}
		}

		bool has3D{};

		// user wants to exit
		if (choose3D == -1) { break; }

		// movie has 3D
		else if (choose3D == 1) { has3D = true; }

		// movie hasn't got 3D
		else if (choose3D == 2) { has3D = false; }

		Movie movie(mName, mGenre, mHours, mMins, mMinAge, hasPLDub, has3D); // creating user's movie
		movies.push_back(movie); // adding user's movie

		cout << "\nMovie was added. Movie info below:";
		movie.info(); break;

	} // while addMovie (2)
}

// Implementation of the menuDeleteMovie method
void CinemaInterface::menuDeleteMovie()
{
	while (true) // 2. chooseDelete
	{
		// if there are no movies yet - it breakes
		if (wereMoviesInitialized() == false) { break; }

		cout << "\nPossible options: \n1. Delete all movies.\n2. Delete a movie.";

		int chooseDelete{};
		// checking chooseDelete validity
		while (true)
		{
			cout << "\nType your choice: ";
			if (isInputInt(chooseDelete) == true) // if inputted value isInt
			{
				if (chooseDelete == -1) { break; } // user wants to exit
				else if (isInRange(1, 2, chooseDelete) == true) { break; } // if inputted value isInRange
			}
		}

		// user wants to exit
		if (chooseDelete == -1) { break; }

		// user wants to delete all movies
		else if (chooseDelete == 1)
		{
			int moviesSize = movies.size(); // loop for checks his range with every iteration - so we need to get our movies.size() at constant integer
			for (int i = 0; i < moviesSize; i++)
			{
				movies.pop_back();
			}
			cout << "\nAll movies were deleted.";
		}

		// user wants to delete a movie
		else if (chooseDelete == 2)
		{
			cout << "\nMovies list:\n";
			menuShowMovies(false, false);

			while (true) // 3. movieDelete
			{

				int chooseMovie{};
				// checking chooseMovie validity
				while (true)
				{
					cout << "\nType movie's number you want to delete: ";
					if (isInputInt(chooseMovie) == true) // if inputted value isInt
					{
						if (chooseMovie == -1) { break; } // if user typed -1 we exi
						else if (isInRange(1, movies.size(), chooseMovie) == true) { break; } // if inputted value isInRange
					}
				}

				// if user wants to exit
				if (chooseMovie == -1) { break; }

				else
				{
					string deletedName = movies[chooseMovie - 1].get_name();
					movies.erase(movies.begin() + chooseMovie - 1); // deleting movie that user chose
					cout << "\nMovie called \"" << deletedName << "\" was deleted.";
				}
			} // while movieDelete (3)

		}


	} // while chooseDelete (2)
}

// Implementation of the menuAddRoom method
void CinemaInterface::menuAddRoom()
{
	while (true) // 2. addRoom
	{
		cout << "\nBe careful with your inputs - inputting ,-1, wont take you back to last movie parameter, but to previous menu.";

		// number must be precise - because other way map ,,rooms'' in class Track will create default to fill the gaps between numbers
		int rNumber = rooms.size();

		// user inputs row number
		int rRows{};
		// checking rRows validity
		while (true)
		{
			cout << "\nEnter how many rows your room has: ";
			if (isInputInt(rRows) == true)
			{
				if (rRows == -1) { break; }
				else if (isInRange(1, 20, rRows) == true) { break; }
			}
		}

		if (rRows == -1) { break; } // user wants to exit

		// user inputs columns number
		int rColumns{};
		// checking rRows validity
		while (true)
		{
			cout << "\nEnter how many columns your room has: ";
			if (isInputInt(rColumns) == true)
			{
				if (rColumns == -1) { break; }
				else if (isInRange(1, 20, rColumns) == true) { break; }
			}
		}

		if (rColumns == -1) { break; } // user wants to exit


		int choose3D{}; // can room display 3D
		cout << "\nCan your room display 3D?:\n1. Yes.\n2. No.";
		// checking choose3D validity
		while (true)
		{
			cout << "\nType your answer: ";
			if (isInputInt(choose3D) == true) // if inputted value isInt
			{
				if (choose3D == -1) { break; } // user wants to exit
				else if (isInRange(1, 2, choose3D) == true) { break; } // if inputted value isInRange
			}
		}

		bool rDisplay3D{};

		// user wants to exit
		if (choose3D == -1) { break; }

		// room can display 3D
		else if (choose3D == 1) { rDisplay3D = true; }

		// room can't display 3D
		else if (choose3D == 2) { rDisplay3D = false; }

		Room room(rNumber, rRows, rColumns, rDisplay3D);
		rooms.push_back(room);

		cout << "\nRoom was added. Room info below:";
		room.onlyRoomInfo(); cout << endl; break;
	} // while addRoom (2)
}

// Implementation of the menuDeleteRoom method
void CinemaInterface::menuDeleteRoom()
{
	while (true) // 2. chooseDelete
	{
		// if there are no movies yet - it breakes
		if (wereRoomsInitialized() == false) { break; }

		cout << "\nPossible options: \n1. Delete all rooms.\n2. Delete a room.";

		int chooseDelete{};
		// checking chooseDelete validity
		while (true)
		{
			cout << "\nType your choice: ";
			if (isInputInt(chooseDelete) == true) // if inputted value isInt
			{
				if (chooseDelete == -1) { break; } // user wants to exit
				else if (isInRange(1, 2, chooseDelete) == true) { break; } // if inputted value isInRange
			}
		}

		// user wants to exit
		if (chooseDelete == -1) { break; }

		// user wants to delete all rooms
		else if (chooseDelete == 1)
		{
			int roomsSize = rooms.size(); // loop for checks his range with every iteration - so we need to get our rooms.size() at constant integer
			for (int i = 0; i < roomsSize; i++)
			{
				rooms.pop_back();
			}
			cout << "\nAll rooms were deleted.";
		}

		// user wants to delete a room
		else if (chooseDelete == 2)
		{
			cout << "\nAfter you delete chosen room, remember that all the other rooms will change their numbers to in sequence.";
			while (true) // 3. deleteRoom
			{
				int chooseRoom{};
				//checking chooseRoom validity
				while (true)
				{
					cout << "\nType number of room you want to delete: ";
					if (isInputInt(chooseRoom) == true)
					{
						if (chooseRoom == -1) { break; } // user wants to exit
						else if (isInRange(1, rooms.size(), chooseRoom) == true) { break; }
					}
				}

				// user wants to exit
				if (chooseRoom == -1) { break; }

				// user chose room to delete
				else
				{
					rooms.erase(rooms.begin() + chooseRoom - 1); // deleting user's room;
					cout << "\nRoom " << chooseRoom << " was deleted.";
					// assigning all rooms new numbers
					for (int r = 0; r < rooms.size(); r++)
					{
						rooms[r].set_number(r);
					}
				}
			} // while deleteRoom (3)

		}

	} // while chooseDelete (2)
}

// Implementation of the resetDaySchedule method
void CinemaInterface::resetDaySchedule()
{
	while (true) // 3. chooseDay
	{

		cout << "\nDays:";
		for (int day = 0; day < week.size(); day++) // printing out avaiable days
		{
			cout << "\n" << day + 1 << ". " << days[day];
		}


		int chooseDay{};
		// checking chooseDay validity
		while (true) // 3a.
		{
			cout << "\nEnter number of day which schedule you want to reset: ";
			if (isInputInt(chooseDay) == true)
			{
				if (chooseDay == -1) { break; } // we exit and go back to chooseDay (2)
				else if (isInRange(1, week.size(), chooseDay) == true) { break; } // if inputted value isInRange
			}
		}

		// user wants to exit
		if (chooseDay == -1) { break; }

		// user chose a day
		else
		{
			while (true) // 4. choosePeriod
			{
				cout << "\nWhat schedule do you want to reset:";
				cout << "\n1. Room.";
				cout << "\n2. Whole day.";

				int choosePeriod{};
				// checking choosePeriod validity
				while (true) // 4a.
				{
					cout << "\nWhich one do you choose: ";
					if (isInputInt(choosePeriod) == true)
					{
						if (choosePeriod == -1) { break; } // we exit and go back to chooseOption (3)
						else if (isInRange(1, 2, choosePeriod) == true) { break; } // if inputted value isInRange
					}
				}

				// user wants to exit
				if (choosePeriod == -1) { break; }

				// user chose to reset particular room's schedule
				else if (choosePeriod == 1)
				{
					while (true) // 5. chooseRoom
					{
						cout << "\nAvaiable rooms:";
						for (int i = 0; i < week[chooseDay - 1].get_rooms().size(); i++)
						{
							week[chooseDay - 1].get_rooms()[i].onlyRoomInfo(false);
						}

						int chooseRoom{};
						// checking chooseRoom validity
						while (true) // 5a.
						{
							cout << "\nPlease enter room's number which schedule you want to reset: ";
							if (isInputInt(chooseRoom) == true)
							{
								if (chooseRoom == -1) { break; } // we exit and go back to chooseAction (1)
								else if (isInRange(1, week[chooseDay - 1].get_rooms().size(), chooseRoom) == true) { break; } // if inputted value isInRange
							}
						}

						// user wants to exit
						if (chooseRoom == -1) { break; }

						// user chose a room
						else
						{
							week[chooseDay - 1].resetRoomSchedule(week[chooseDay - 1].get_rooms()[chooseRoom - 1], false);
							cout << "\nRoom's schedule has been resetted.";
						}

					} // while chooseRoom (5)
				}

				// user chose to reset whole day schedule
				else if (choosePeriod == 2)
				{
					week[chooseDay - 1].resetTodaysSchedule(false);
					cout << endl << days[chooseDay - 1] << "'s schedule has been resetted.";
				}

			} // while choosePeriod (4)
		}

	} // while chooseDay (3)
}

// Implementation of the resetWeekSchedule method
void CinemaInterface::resetWeekSchedule(bool inform)
{
	for (int i = 0; i < week.size(); i++)
	{
		week[i].resetTodaysSchedule(false);
	}
	if (inform == true) { cout << "\nWhole week schedule has been resetted."; }
}

// Implementation of the manuallyAddMovie method
void CinemaInterface::manuallyAddMovie()
{
	// to allow user to exitNow at the end
	bool exitNow = false;

	while (true) // 2. chooseDay
	{
		// to allow user to goBackToChooseDay at the end
		bool goBackToChooseDay = false;

		// user chose to exitNow at the end
		if (exitNow == true) { break; }

		cout << "\nDays:";
		for (int day = 0; day < week.size(); day++) // printing out avaiable days
		{
			cout << "\n" << day + 1 << ". " << days[day];
		}


		int chooseDay{};
		// checking chooseDay validity
		while (true) // 2a.
		{
			cout << "\nInput ,0, to show day's schedule. Enter number of day in which schedule you want to add movie: ";
			if (isInputInt(chooseDay) == true)
			{
				if (chooseDay == -1) { break; } // we exit and go back to chooseAction (1)
				else if (chooseDay == 0) { break; } // user wants to see day's schedule
				else if (isInRange(1, week.size(), chooseDay) == true) { break; } // if inputted value isInRange
			}
		}

		// user wants to exit
		if (chooseDay == -1) { break; }

		// user wants to see day's schedule
		else if (chooseDay == 0)
		{
			int chooseScheduleDay{};
			// checking chooseScheduleDay validity
			while (true) // 2b.
			{
				cout << "\nEnter number of day which schedule you want to see: ";
				if (isInputInt(chooseScheduleDay) == true)
				{
					if (chooseScheduleDay == -1) { break; } // we exit and go back to chooseDay (2)
					else if (isInRange(1, week.size(), chooseScheduleDay) == true) { break; } // if inputted value isInRange
				}
			}

			// user wants to exit
			if (chooseScheduleDay == -1) {}

			// user chose a Day
			else
			{
				showDaySchedule(chooseScheduleDay);
			}


		}


		// user chose a day
		else
		{
			while (true) // 3. chooseRoom
			{
				// to allow user to goBackToChooseRoom at the end
				bool goBackToChooseRoom = false;

				// user chose to goBackToChooseDay at the end
				if (goBackToChooseDay == true) { break; }
				// user chose to exitNow at the end
				if (exitNow == true) { break; }

				cout << "\nAvaiable rooms:";
				for (int i = 0; i < week[chooseDay - 1].get_rooms().size(); i++)
				{
					week[chooseDay - 1].get_rooms()[i].onlyRoomInfo(false);
				}

				int chooseRoom{};
				// checking chooseRoom validity
				while (true) // 3a.
				{
					cout << "\nInput ,0, to show room's schedule. Enter room's number in which schedule you want to set movie: ";
					if (isInputInt(chooseRoom) == true)
					{
						if (chooseRoom == -1) { break; } // we exit and go back to chooseDay (2)
						if (chooseRoom == 0) { break; } // user wants to see rooms' schedule
						else if (isInRange(1, week[chooseDay - 1].get_rooms().size(), chooseRoom) == true) { break; } // if inputted value isInRange
					}
				}

				// user wants to exit
				if (chooseRoom == -1) { break; }

				// user wants to see room's schedule
				else if (chooseRoom == 0)
				{
					int chooseRoomSchedule{};
					// checking chooseRoomSchedule validity
					while (true) // 3b.
					{
						cout << "\nEnter room's number which schedule you want to see: ";
						if (isInputInt(chooseRoomSchedule) == true)
						{
							if (chooseRoomSchedule == -1) { break; } // we exit and go back to chooseRoom (3)
							else if (isInRange(1, week[chooseDay - 1].get_rooms().size(), chooseRoomSchedule) == true)
							{
								week[chooseDay - 1].showRoomSchedule(week[chooseDay - 1].get_rooms()[chooseRoomSchedule - 1]);
								break;
							}

						}
					}
				}

				// user chose a room
				else
				{

					while (true) // 4. chooseMovie
					{
						// user chose to goBackToChooseRoom at the end
						if (goBackToChooseRoom == true) { break; }
						// user chose to goBackToChooseDay at the end
						if (goBackToChooseDay == true) { break; }
						// user chose to exitNow at the end
						if (exitNow == true) { break; }


						cout << "\nChoose movie that you want to set from list below:\n";
						menuShowMovies(false, false);

						int chooseMovie{};
						// checking chooseMovie validity
						while (true)
						{
							cout << "\nYou can input ,0, to get more information about movies or enter movie's number: ";
							if (isInputInt(chooseMovie) == true) // if inputted value isInt
							{
								if (chooseMovie == -1) { break; } // if user typed -1 we exit
								else if (chooseMovie == 0) { break; } // user wants to gather more information
								else if (isInRange(1, movies.size(), chooseMovie) == true) { break; } // if inputted value isInRange
							}
						}

						// if user wants to exit
						if (chooseMovie == -1) { break; }

						// user wants to get more information
						else if (chooseMovie == 0)
						{
							menuShowMovies(true, false);
						}

						// user chose a movie
						else
						{
							while (true) // 5. choosingHours
							{

								int startHour{}, startMins{};
								while (true) // 5a.
								{

									while (true) // checking if startHour is integer
									{
										cout << "\nAt which hour you want your movie to start?: ";
										if (isInputInt(startHour) == true) { break; }
									}

									if (startHour == -1) { break; } // user wants to exit

									while (true) // checking if startMins is integer
									{
										cout << "\nAnd which minutes?: ";
										if (isInputInt(startMins) == true) { break; }
									}

									// if inputted values are correct - we can proceed
									if (startMins == -1) { break; }
									else if (checkIsTimeCorrect(startHour, startMins) == true) { break; }
								}

								// user wants to exit
								if (startHour == -1 || startMins == -1) { break; }

								// trying to set user's chosen movie
								else
								{
									// if movie was set
									if (week[chooseDay - 1].setMovie(week[chooseDay - 1].get_rooms()[chooseRoom - 1], movies[chooseMovie - 1], startHour, startMins) == true)
									{
										cout << "\nTo which choosing you want to go back:\n1. Start hours. \n2. Movies.";
										cout << "\n3. Rooms.\n4. Days. \n5. Exit to schedule's menu.";

										int chooseExit{};
										// checking chooseExit validity
										while (true)
										{
											cout << "\nEnter your choice: ";
											if (isInputInt(chooseExit) == true)
											{
												if (isInRange(1, 5, chooseExit) == true) { break; }
											}
										}

										// user wants to go back to choosingHours
										if (chooseExit == 1) {}

										// user wants to go back to choseMovie
										else if (chooseExit == 2) { break; }

										// user wants to go back to chooseRoom
										else if (chooseExit == 3)
										{
											goBackToChooseRoom = true;
											break;
										}

										// user wants to go back to chooseDay
										else if (chooseExit == 4)
										{
											goBackToChooseDay = true;
											break;
										}

										// user wants to exit immediately
										else if (chooseExit == 5)
										{
											exitNow = true;
											break;
										}
									}

									// movie wasn't set
									else {}
								}

							} // while choosingHours (5)
						}

					} // while chooseMovie (4)
				}

			} // while chooseRoom (3)

		} // user chose a day

	} // while chooseDay (2)
}

// Implementation of the manuallyDeleteMovie method
void CinemaInterface::manuallyDeleteMovie()
{
	// to allow user to exitNow at the end
	bool exitNow = false;

	while (true) // 2. chooseDay
	{
		// to allow user to goBackToChooseDay at the end
		bool goBackToChooseDay = false;

		// user chose to exitNow at the end
		if (exitNow == true) { break; }

		cout << "\nDays:";
		for (int day = 0; day < week.size(); day++) // printing out avaiable days
		{
			cout << "\n" << day + 1 << ". " << days[day];
		}


		int chooseDay{};
		// checking chooseDay validity
		while (true) // 2a.
		{
			cout << "\nInput ,0, to show day's schedule. Enter number of day in which schedule you want to delete movie: ";
			if (isInputInt(chooseDay) == true)
			{
				if (chooseDay == -1) { break; } // we exit and go back to chooseAction (1)
				else if (chooseDay == 0) { break; } // user wants to see day's schedule
				else if (isInRange(1, week.size(), chooseDay) == true) { break; } // if inputted value isInRange
			}
		}

		// user wants to exit
		if (chooseDay == -1) { break; }

		// user wants to see day's schedule
		else if (chooseDay == 0)
		{
			int chooseScheduleDay{};
			// checking chooseScheduleDay validity
			while (true) // 2b.
			{
				cout << "\nEnter number of day which schedule you want to see: ";
				if (isInputInt(chooseScheduleDay) == true)
				{
					if (chooseScheduleDay == -1) { break; } // we exit and go back to chooseDay (2)
					else if (isInRange(1, week.size(), chooseScheduleDay) == true) { break; } // if inputted value isInRange
				}
			}

			// user wants to exit
			if (chooseScheduleDay == -1) {}

			// user chose a Day
			else
			{
				showDaySchedule(chooseScheduleDay);
			}

		}

		// user chose a day
		else
		{
			while (true) // 3. chooseMovie
			{

				// user chose to goBackToChooseDay at the end
				if (goBackToChooseDay == true) { break; }
				// user chose to exitNow at the end
				if (exitNow == true) { break; }

				cout << "\nMovies list:\n";
				menuShowMovies(false, false);


				int chooseMovie{};
				// checking chooseMovie validity
				while (true)
				{
					cout << "\Input ,0, to see room's schedule. Choose movie that you want to delete from schedule: ";
					if (isInputInt(chooseMovie) == true) // if inputted value isInt
					{
						if (chooseMovie == -1) { break; } // if user typed -1 we exit
						else if (chooseMovie == 0) { break; } // user wants to see room's schedule
						else if (isInRange(1, movies.size(), chooseMovie) == true) { break; } // if inputted value isInRange
					}
				}

				// user wants to exit
				if (chooseMovie == -1) { break; }

				// user wants to see room's schedule
				else if (chooseMovie == 0)
				{
					int chooseRoomSchedule{};
					// checking chooseRoomSchedule validity
					while (true) // 3b.
					{
						cout << "\nAvaiable rooms:";
						for (int i = 0; i < week[chooseDay - 1].get_rooms().size(); i++)
						{
							week[chooseDay - 1].get_rooms()[i].onlyRoomInfo(false);
						}
						cout << "\nEnter room's number which schedule you want to see: ";
						if (isInputInt(chooseRoomSchedule) == true)
						{
							if (chooseRoomSchedule == -1) { break; } // we exit and go back to chooseRoom (3)
							else if (isInRange(1, week[chooseDay - 1].get_rooms().size(), chooseRoomSchedule) == true)
							{
								week[chooseDay - 1].showRoomSchedule(week[chooseDay - 1].get_rooms()[chooseRoomSchedule - 1]);
								break;
							}

						}
					}
				}

				// user chose movie
				else
				{

					while (true) // 4. chooseIteration
					{

						cout << "\nShowing when and where movie \"" << movies[chooseMovie - 1].get_name() << "\" is playing:\n";

						map<vector<int>, vector<int>> movieSearchInDay;
						movieSearchInDay = week[chooseDay - 1].searchForMovie(movies[chooseMovie - 1], true, true); // printing out when and where

						int chooseIteration{};
						//checking chooseIteration validity
						while (true) // 4.
						{
							cout << "Now please choose which movie you want to delete entering number of movie iteration: ";
							if (isInputInt(chooseIteration) == true) // if inputted value isInt
							{
								if (chooseIteration == -1) { break; } // if user typed -1 we exit and go back to chooseMovie (2)
								else if (isInRange(1, movieSearchInDay.size(), chooseIteration) == true) { break; } // if inputted value isInRange
							}
						}

						if (chooseIteration == -1) { break; } // if user typed -1 we exit and go back to chooseMovie(3)

						// user has selected an iteration
						else
						{
							// we will use iteration to find user chooseIteration and get info needed to buy him ticket
							int iteration = 1;
							int roomNumber{};
							int movieStartHour{};
							int movieStartMin{};
							int movieEndHour{};
							int movieEndMin{};


							// going through every map element in user chosen week day
							for (const auto& entry : movieSearchInDay)
							{
								// if we find our user chooseIteration
								if (chooseIteration == iteration)
								{
									roomNumber = entry.first[0]; // getting chooseIteration roomNumber
									movieStartHour = entry.second[0];
									movieStartMin = entry.second[1];
									movieEndHour = entry.second[2];
									movieEndMin = entry.second[3];
								}

								iteration = iteration + 1;
							}


							// trying to delete movie
							week[chooseDay - 1].deleteMovie(week[chooseDay - 1].get_rooms()[roomNumber], movies[chooseMovie - 1], movieStartHour, movieStartMin, movieEndHour, movieEndMin);

							cout << "\nTo which choosing you want to go back:\n1. Movie iterations. \n2. Movies.";
							cout << "\n3. Days. \n4. Exit to schedule's menu.";

							int chooseExit{};
							// checking chooseExit validity
							while (true)
							{
								cout << "\nEnter your choice: ";
								if (isInputInt(chooseExit) == true)
								{
									if (isInRange(1, 5, chooseExit) == true) { break; }
								}
							}

							// user wants to go back to choosingHours
							if (chooseExit == 1) {}

							// user wants to go back to choseMovie
							else if (chooseExit == 2) { break; }

							// user wants to go back to chooseDay
							else if (chooseExit == 3)
							{
								goBackToChooseDay = true;
								break;
							}

							// user wants to exit immediately
							else if (chooseExit == 4)
							{
								exitNow = true;
								break;
							}

						}

					} // while chooseIteration (4)

				} // user chose a movie

			} // while chooseMovie (3)

		} // user chose a day

	} // while chooseDay (2)
}

// Implementation of the managerMenu method
void CinemaInterface::managerMenu()
{
	while (true) // 0. managerMenu
	{
		cout << "\n**************************MAIN MENU***********************************";
		cout << "\nWelcome to cinema manager menu, you can input '0' to get instructions how this menu works";
		cout << "\nAVAIABLE COMMANDS:";
		cout << "\n1. Create/delete movie or show movies list.";
		cout << "\n2. Create/delete room or show all rooms.";
		cout << "\n3. Initialize/delete cinema opening days or show them.";
		cout << "\n4. Generate new schedule, manually add/delete movies, show schedules.";
		cout << "\n5. Clear console window.";
		cout << endl;


		int chooseCom{}; // shortcut for chooseCommand
		// checking chooseCom validity
		while (true)
		{
			cout << "\nChoose what you want to do by writing number: ";

			if (isInputInt(chooseCom) == true) // if inputted value isInt
			{
				if (chooseCom == -1) { break; } // user wants to exit
				else if (chooseCom == 0) { break; } // user wants to get Helper
				else if (isInRange(1, 5, chooseCom) == true) { break; } // if inputted value isInRange
			}
		}

		// user wants to exit
		if (chooseCom == -1) { break; }

		// user wants to get some instructions
		else if (chooseCom == 0)
		{
			cout << "\n\nSo, at first you need to initialize(create) some movies by '1' in menu. Movies and rooms have built-in base, that you can use,";
			cout << "\nbut it's not necessary to use them and you can create as much objects as you want:). After doing that you need to ";
			cout << "\ninitialize some rooms, too ('2' in menu). Then you can proceed to '3' and choose your cinema opening hours in picked days.";
			cout << "\nVERY IMPORTANT: Remember to use option nr. 5 (Load all initialiazed rooms to days' tracks) in this menu after choosing your";
			cout << "\nopen hours - YOU WON'T BE ABLE TO generate/modify schedule without it.";
			cout << "\nAlso remember that adding new rooms/movies won't change schedule unless you do all the above steps again.";
			cout << "\nAnd last thing: if you use nr. 5 in '3' menu again, without changing anything, it will reset your schedule anyway!";
			cout << "\nHope you will have fun with my program B)).\n";
		}

		// user wants to add/delete movies or just show them
		else if (chooseCom == 1)
		{
			if (movies.size() != 0) { menuShowMovies(false, true); } // if we got any movies - we show them
			while (true) // 1. chooseAction
			{
				// there are no movies initialized yet
				if (movies.size() == 0)
				{
					cout << "\n-------------------------------------------------";
					cout << "\nThere are no movies yet.\nYou can add them manually or do you want to initalize default movie base?:";
					cout << "\n1. Initialize built-in movie base.\n2. Don't initialize it.";
					cout << "\nType your choice: ";

					int chooseInit{}; // shortcut for chooseInitialization
					// checking chooseInit validity
					while (true)
					{
						if (isInputInt(chooseInit) == true) // if inputted value isInt
						{
							if (chooseInit == -1) { break; } // user wants to exit
							else if (isInRange(1, 2, chooseInit) == true) { break; } // if inputted value isInRange
						}
					}

					// user wants to exit
					if (chooseInit == -1) { break; }

					// user wants to initialize built-in movie base
					else if (chooseInit == 1)
					{
						movieSetter();
					}

					// user don't want to initialize built-in movie base
					else if (chooseInit == 2)
					{
						cout << "\nRemember that you can always initialize built-in movie base if you have 0 movies.";
					}
				}

				cout << "\nPossible actions:\n1. Add new movie.\n2. Delete all/a movie.";
				cout << "\n3. Reshow movies list.";

				int chooseAction{};
				// checking chooseAction validity
				while (true)
				{
					cout << "\nWhat do you want to do: ";
					if (isInputInt(chooseAction) == true) // if inputted value isInt
					{
						if (chooseAction == -1) { break; } // user wants to exit
						else if (isInRange(1, 3, chooseAction) == true) { break; } // if inputted value isInRange
					}
				}

				// user wants to exit to menu
				if (chooseAction == -1) { break; }

				// user wants to add new movie
				else if (chooseAction == 1)
				{
					menuAddMovie();
				}

				// user wants to delete a movie
				else if (chooseAction == 2)
				{
					menuDeleteMovie();
				}

				// user wants to reshow movies list
				else if (chooseAction == 3)
				{
					// if movies weren't initialized shows error and go back to menu
					if (wereMoviesInitialized() == false) {}

					else
					{
						cout << "\n\nMovies list:\n";
						menuShowMovies(true, false);
					}
				}

			} // while chooseAction (1)
		}

		// user wants to add/delete rooms or just show them
		else if (chooseCom == 2)
		{
			if (rooms.size() != 0) { showRooms(); cout << endl; } // if we got any rooms - we show them
			while (true) // 1. chooseAction
			{
				// there are no rooms initialized yet
				if (rooms.size() == 0)
				{
					cout << "\n-------------------------------------------------";
					cout << "\nThere are no rooms yet.\nYou can add them manually or do you want to initalize default room base?:";
					cout << "\n1. Initialize built-in room base.\n2. Don't initialize it.";
					cout << "\nType your choice: ";

					int chooseInit{}; // shortcut for chooseInitialization
					// checking chooseInit validity
					while (true)
					{
						if (isInputInt(chooseInit) == true) // if inputted value isInt
						{
							if (chooseInit == -1) { break; } // user wants to exit
							else if (isInRange(1, 2, chooseInit) == true) { break; } // if inputted value isInRange
						}
					}

					// user wants to exit
					if (chooseInit == -1) { break; }

					// user wants to initialize built-in room base
					else if (chooseInit == 1)
					{
						roomSetter();
					}

					// user don't want to initialize built-in movie base
					else if (chooseInit == 2)
					{
						cout << "\nRemember that you can always initialize built-in room base if you have 0 rooms.";
					}
				}

				cout << "\nPossible actions:\n1. Add new room.\n2. Delete all/a room.";
				cout << "\n3. Reshow rooms list.";

				int chooseAction{};
				// checking chooseAction validity
				while (true)
				{
					cout << "\nWhat do you want to do: ";
					if (isInputInt(chooseAction) == true) // if inputted value isInt
					{
						if (chooseAction == -1) { break; } // user wants to exit
						else if (isInRange(1, 3, chooseAction) == true) { break; } // if inputted value isInRange
					}
				}

				// user wants to exit to menu
				if (chooseAction == -1) { break; }

				// user wants to add new room
				else if (chooseAction == 1)
				{
					menuAddRoom();
				}

				// user wants to delete all/a room
				else if (chooseAction == 2)
				{
					menuDeleteRoom();
				}

				// user wants to reshow rooms list
				else if (chooseAction == 3)
				{
					// if movies weren't initialized shows error and go back to menu
					if (wereRoomsInitialized() == false) {}

					else
					{
						showRooms();
						cout << endl;
					}

				}

			} // while chooseAction (1)
		}

		// user wants to pick cinema open/closing hours
		else if (chooseCom == 3)
		{
			if (wereRoomsLoaded(false) == false)
			{
				cout << "\nVERY IMPORTANT: Remember to use option nr. 5 (Load all initialiazed rooms to days' tracks) in this menu after choosing your";
				cout << "\nopen hours - YOU WON'T BE ABLE TO generate/modify schedule without it.";
			}

			while (true) // 1.chooseAction
			{
				bool allDone = false;
				// checking if movies are initialized
				if (wereMoviesInitialized() == false)
				{
					cout << "\nYou need to have at least one movie initialized to proceed. Please go add some and come back.";
					break;
				}

				// checking if rooms are initialized
				if (wereRoomsInitialized() == false)
				{
					cout << "\nYou need to have at least one room initialized to proceed. Please go add some and come back.";
					break;
				}

				cout << "\nTrack's menu commands:";
				cout << "\n1. Automatically initialization - in all days cinema is open 13:00 - 23:00.";
				cout << "\n2. Manually initialization - you can pick cinema open hours in all/some days.";
				cout << "\n3. Delete all days.";
				cout << "\n4. Show days' cinema opening hours.";
				cout << "\n5. Load all initialiazed rooms to days' tracks";

				int chooseAction{};
				// checking chooseAction validity
				while (true)
				{
					cout << "\nWhich one do you choose: ";

					if (isInputInt(chooseAction) == true) // if inputted value isInt
					{
						if (chooseAction == -1) { break; } // user wants to exit
						else if (isInRange(1, 5, chooseAction) == true) { break; } // if inputted value isInRange
					}
				}

				// user wants to exit
				if (chooseAction == -1) { break; }

				// user prefer automatic track setting
				else if (chooseAction == 1)
				{
					// user has initialized all days
					if (week.size() == 7)
					{
						cout << "\n***ERROR: All days opening hours have been set!***";
					}

					else
					{
						trackSetter();
						cout << "\nTracks were set.";
					}

				}

				// user prefer manually track setting
				else if (chooseAction == 2)
				{
					while (true) // 2. chooseOption
					{
						// if we done we exit
						if (allDone == true) { break; }

						// user has initialized all days
						if (week.size() == 7)
						{
							cout << "\n***ERROR: All days opening hours have been set!***";
							break;
						}

						// if theres no all days initialized
						else
						{
							cout << "\nYou will now choose default opening hours for days - but later u can select any day and personalize its hours";
							int openHour{}, openMin{}, closeHour{}, closeMin{};

							// checking if inputs are integers
							while (true)
							{
								cout << "\nPlease enter cinema OPENING HOUR: ";
								if (isInputInt(openHour) == true)
								{
									if (openHour == -1) { break; }
									else if (isInRange(0, 23, openHour) == true) { break; }
								}
							}
							if (openHour == -1) { break; } // user wants to exit

							while (true)
							{
								cout << "\nPlease enter cinema OPENING MINUTE: ";
								if (isInputInt(openMin) == true)
								{
									if (openMin == -1) { break; }
									else if (isInRange(0, 59, openMin) == true) { break; }
								}
							}
							if (openMin == -1) { break; } // user wants to exit

							while (true)
							{
								cout << "\nPlease enter cinema CLOSING HOUR: ";
								if (isInputInt(closeHour) == true)
								{
									if (closeHour == -1) { break; }
									else if (isInRange(0, 23, closeHour) == true) { break; }
								}
							}
							if (closeHour == -1) { break; } // user wants to exit

							while (true)
							{
								cout << "\nPlease enter cinema CLOSING MINUTE: ";
								if (isInputInt(closeMin) == true)
								{
									if (closeMin == -1) { break; }
									else if (isInRange(0, 59, closeMin) == true) { break; }
								}
							}
							if (closeMin == -1) { break; } // user wants to exit

							cout << "\nNow choose days which you want to have personalized hours.";
							cout << "\nSo if you want to f.e have different cinema working hours in the weekend - choose Saturday and Sunday.";
							cout << "\nBe careful - start with least number - after chosing Friday you can't change Monday's hours.";
							cout << "\nDays:";
							for (int day = 0; day < days.size(); day++)
							{
								cout << endl << day + 1 << ". " << days[day];
							}

							while (true) // 3. personalizeDays
							{
								// user has initialized all days
								if (week.size() == 7)
								{
									cout << "\nAll days opening hours have been set!";
									cout << endl;
									allDone = true;
									break;
								}

								int chooseDay{};
								// checking chooseDay validity
								while (true)
								{
									cout << "\nWhen you done - input ,0,. Choose day: ";
									if (isInputInt(chooseDay) == true)
									{
										if (chooseDay == -1) { break; }
										else if (chooseDay == 0) { break; }
										else if (isInRange(1, days.size(), chooseDay) == true) { break; }
									}
								}

								// if user wants to exit he will end up at start point of chooseOption (2)
								if (chooseDay == -1) { break; }

								// user is done choosing hours
								else if (chooseDay == 0)
								{
									// adding days with default user's hours if days are missing
									if (week.size() != 7)
									{
										for (int i = week.size(); i < 7; i++)
										{
											Track trackDay(openHour, openMin, closeHour, closeMin);
											week.push_back(trackDay);
										}
									}
									printOutTracksHours();
									cout << "\nAll days opening hours have been set.";
									cout << endl;
									allDone = true; break;
								}

								// user chose a day
								else
								{
									// user has chosen earlier day than before
									if (chooseDay <= week.size())
									{
										cout << "\n*ERROR: You can't go back to previous days.***";
									}

									// user chose day correctly
									else
									{
										// creating days with user's default opening hours TO day which hours he want to personalize
										for (int i = week.size(); i < chooseDay - 1; i++)
										{
											Track trackDay(openHour, openMin, closeHour, closeMin);
											week.push_back(trackDay);
										}

										cout << "\nYou can't go back with ,-1, unless you enter all time values correctly";

										int pOpenHour{}, pOpenMin{}, pCloseHour{}, pCloseMin{};
										// checking if inputs are integers
										while (true)
										{
											cout << "\nPlease enter cinema OPENING HOUR: ";
											if (isInputInt(pOpenHour) == true)
											{
												if (isInRange(0, 23, pOpenHour) == true) { break; }
											}
										}

										while (true)
										{
											cout << "\nPlease enter cinema OPENING MINUTE: ";
											if (isInputInt(pOpenMin) == true)
											{
												if (isInRange(0, 59, pOpenMin) == true) { break; }
											}
										}

										while (true)
										{
											cout << "\nPlease enter cinema CLOSING HOUR: ";
											if (isInputInt(pCloseHour) == true)
											{
												if (isInRange(0, 23, pCloseHour) == true) { break; }
											}
										}

										while (true)
										{
											cout << "\nPlease enter cinema CLOSING MINUTE: ";
											if (isInputInt(pCloseMin) == true)
											{
												if (isInRange(0, 59, pCloseMin) == true) { break; }
											}
										}

										// adding user new trackDay to the week
										Track trackDay(pOpenHour, pOpenMin, pCloseHour, pCloseMin);
										week.push_back(trackDay);

										// printing out days with opening hours
										printOutTracksHours();
										cout << "\nDay's opening hours was set.";
									}
								}

							} // while personalizeDays (3)
						}



					} // while chooseOption (2)
				}

				// user wants to delete all tracks
				else if (chooseAction == 3)
				{
					// if tracks haven't been initialized
					if (wereTracksInitialized() == false) {}

					else
					{
						week.clear();
						cout << "\nAll tracks have been deleted.";
					}
				}

				// user wants to see cinema opening hours
				else if (chooseAction == 4)
				{
					// if tracks haven't been initialized
					if (wereTracksInitialized() == false) {}

					else
					{
						printOutTracksHours();
						cout << endl;
					}
				}

				// user wants to load initialized rooms into tracks
				else if (chooseAction == 5)
				{
					// if tracks haven't been initialized
					if (wereTracksInitialized() == false) {}

					else
					{
						loadRoomsIntoTracks();
						cout << "\nAll rooms were set in days' tracks.";
					}

				}


			} // while chooseAction (1)

		}

		// user wants to operate on schedule
		else if (chooseCom == 4)
		{
			while (true) // 1. chooseAction
			{
				// if tracks weren't initialized
				if (wereTracksInitialized() == false) { break; }

				// if rooms weren't loaded into tracks
				if (wereRoomsLoaded() == false) { break; }

				cout << "\nSchedule menu:";
				cout << "\n1. Regenerate schedule.";
				cout << "\n2. Manually add new movie to schedule.";
				cout << "\n3. Delete movie from schedule.";
				cout << "\n4. Reset schedule.";
				cout << "\n5. Show week/day schedule.";
				cout << "\n6. Show when and where movie is playing.";

				int chooseAction{};
				// checking chooseAction validity
				while (true)
				{
					cout << "\nWhich one do you choose: ";

					if (isInputInt(chooseAction) == true) // if inputted value isInt
					{
						if (chooseAction == -1) { break; } // user wants to exit
						else if (isInRange(1, 6, chooseAction) == true) { break; } // if inputted value isInRange
					}
				}

				// user wants to exit
				if (chooseAction == -1) { break; }

				// user wants to regenerate schedule
				else if (chooseAction == 1)
				{

					while (true) // 2. chooseOption
					{

						cout << "\nYou can regenerate schedule in particular time periods displayed below:";
						cout << "\n1. Day.";
						cout << "\n2. Week.";

						int chooseOption{};
						// checking chooseOption validity
						while (true) // 2a.
						{
							cout << "\nWhich one you want to regenerate: ";
							if (isInputInt(chooseOption) == true)
							{
								if (chooseOption == -1) { break; } // we exit and go back to chooseAction (1)
								else if (isInRange(1, 2, chooseOption) == true) { break; } // if inputted value isInRange
							}
						}

						// user wants to exit
						if (chooseOption == -1) { break; }

						// user wants to regenerate day
						else if (chooseOption == 1)
						{
							while (true) // 3. chooseDay
							{

								cout << "\nDays:";
								for (int day = 0; day < week.size(); day++) // printing out avaiable days
								{
									cout << "\n" << day + 1 << ". " << days[day];
								}


								int chooseDay{};
								// checking chooseDay validity
								while (true) // 3a.
								{
									cout << "\nInput ,0, to show day's schedule. Enter number of day which schedule you want to regenerate: ";
									if (isInputInt(chooseDay) == true)
									{
										if (chooseDay == -1) { break; } // we exit and go back to chooseOption (2)
										else if (chooseDay == 0) { break; } // user wants to see day's schedule
										else if (isInRange(1, week.size(), chooseDay) == true) { break; } // if inputted value isInRange
									}
								}

								// user wants to exit
								if (chooseDay == -1) { break; }

								// user wants to see day's schedule
								else if (chooseDay == 0)
								{
									int chooseScheduleDay{};
									// checking chooseScheduleDay validity
									while (true) // 3b.
									{
										cout << "\nEnter number of day which schedule you want to see: ";
										if (isInputInt(chooseScheduleDay) == true)
										{
											if (chooseScheduleDay == -1) { break; } // we exit and go back to chooseDay (3)
											else if (isInRange(1, week.size(), chooseScheduleDay) == true) { break; } // if inputted value isInRange
										}
									}

									// user wants to exit
									if (chooseScheduleDay == -1) {}

									// user chose a Day
									else
									{
										showDaySchedule(chooseScheduleDay);
									}
								}

								// user chose a day
								else
								{
									while (true) // 4. choosePeriod
									{
										cout << "\nWhat schedule do you want to regenerate:";
										cout << "\n1. Room.";
										cout << "\n2. Whole day.";

										int choosePeriod{};
										// checking choosePeriod validity
										while (true) // 4a.
										{
											cout << "\nWhich one do you choose: ";
											if (isInputInt(choosePeriod) == true)
											{
												if (choosePeriod == -1) { break; } // we exit and go back to chooseDay (3)
												else if (isInRange(1, 2, choosePeriod) == true) { break; } // if inputted value isInRange
											}
										}

										// user wants to exit
										if (choosePeriod == -1) { break; }

										// user chose to regenerate particular room's schedule
										else if (choosePeriod == 1)
										{
											while (true) // 5. chooseRoom
											{
												cout << "\nAvaiable rooms:";
												for (int i = 0; i < week[chooseDay - 1].get_rooms().size(); i++)
												{
													week[chooseDay - 1].get_rooms()[i].onlyRoomInfo(false);
												}

												int chooseRoom{};
												// checking chooseRoom validity
												while (true) // 5a.
												{
													cout << "\nInput ,0, to show room's schedule. Enter room's number which schedule you want to regenerate: ";
													if (isInputInt(chooseRoom) == true)
													{
														if (chooseRoom == -1) { break; } // we exit and go back to choosePeriod (4)
														if (chooseRoom == 0) { break; } // user wants to see rooms' schedule
														else if (isInRange(1, week[chooseDay - 1].get_rooms().size(), chooseRoom) == true) { break; } // if inputted value isInRange
													}
												}

												// user wants to exit
												if (chooseRoom == -1) { break; }

												// user wants to see room's schedule
												else if (chooseRoom == 0)
												{
													int chooseRoomSchedule{};
													// checking chooseRoomSchedule validity
													while (true) // 5b.
													{
														cout << "\nEnter room's number which schedule you want to see: ";
														if (isInputInt(chooseRoomSchedule) == true)
														{
															if (chooseRoomSchedule == -1) { break; } // we exit and go back to chooseRoom (5)
															else if (isInRange(1, week[chooseDay - 1].get_rooms().size(), chooseRoomSchedule) == true)
															{
																week[chooseDay - 1].showRoomSchedule(week[chooseDay - 1].get_rooms()[chooseRoomSchedule - 1]);
																break;
															}

														}
													}
												}

												// user chose a room
												else
												{
													regenerateRoom(chooseDay, chooseRoom);
													cout << "\nRoom's schedule has been regenerated.";
												}

											} // while chooseRoom (5)
										}

										// user chose to regenerate whole day schedule
										else if (choosePeriod == 2)
										{
											regenerateDay(chooseDay);
											cout << endl << days[chooseDay - 1] << "'s schedule has been regenerated.";
											break;
										}

									} // while choosePeriod (4)
								}

							} // while chooseDay (3)
						}

						// user wants to regenerate whole week
						else if (chooseOption == 2)
						{
							cout << "\nThis may take a second.";
							regenerateWeek();
							cout << "\nWeek's schedule has ben regenerated.";
						}

					} // while chooseOption (2)
				}

				// user wants to manually add movie
				else if (chooseAction == 2)
				{
					manuallyAddMovie();
				}

				// user wants to delete movie
				else if (chooseAction == 3)
				{
					manuallyDeleteMovie();
				}

				// user wants to reset schedule
				else if (chooseAction == 4)
				{
					while (true) // 2. chooseOption
					{
						cout << "\nYou can reset schedule in particular time periods displayed below:";
						cout << "\n1. Day.";
						cout << "\n2. Week.";

						int chooseOption{};
						// checking chooseOption validity
						while (true) // 2a.
						{
							cout << "\nWhich one you want to reset: ";
							if (isInputInt(chooseOption) == true)
							{
								if (chooseOption == -1) { break; } // we exit and go back to chooseAction (1)
								else if (isInRange(1, 2, chooseOption) == true) { break; } // if inputted value isInRange
							}
						}

						// user wants to exit
						if (chooseOption == -1) { break; }

						// user wants to reset day
						else if (chooseOption == 1)
						{
							resetDaySchedule();
						}

						// user wants to reset whole week
						else if (chooseOption == 2)
						{
							resetWeekSchedule();
						}

					} // while chooseOption (2)
				}

				// user wants to see schedule
				else if (chooseAction == 5)
				{
					menuShowSchedule();
				}

				// user wants to see when and where movie is playing
				else if (chooseAction == 6)
				{
					menuWhenMovieIsPlaying();
				}

			} // while chooseAction (1)

		}

		// user wants to clear console window
		else if (chooseCom == 5)
		{
			system("cls");
		}


	} // 0. managerMenu
}

// Implementation of the start method
void CinemaInterface::start()
{
	while (true)
	{

		cout << "\nWelcome, program offers you two roles: Client and Cinema Manager.";
		cout << "\nIn client's menu you can buy tickets for movie, see when and where movie is playing or see schedule.";
		cout << "\nCinema manager menu is more advanced - you can create/delete movies, rooms, change cinema open hours, \nregenerate schedule or edit it manually. Changes here will affect schedule that client's operate on.";
		cout << "\nYou will be choosing by inputting numbers. Remember that you can ALWAYS go back by inputting '-1' (apart from here).";
		cout << "\nThere can be also mentioned other special inputs (f.e for showing schedules). ";
		cout << "\nSo, it's time to get started, who do you want to be?:\n1. Client.\n2. Cinema Manager.\n";
		int roleChoose{};
		// checking roleChoose validity
		while (true)
		{
			cout << "Choose by inputting number: ";

			if (isInputInt(roleChoose) == true) // if inputted value isInt
			{
				if (isInRange(1, 2, roleChoose) == true) { break; } // if inputted value isInRange
			}
		}


		// if user chosed to be a client
		if (roleChoose == 1)
		{
			cout << "\nYou chose to be a client! ";

			if (users.size() != 0)
			{
				cout << "You can create new user profile by inputting ,0,. Client's profiles below: ";
				for (int i = 0; i < users.size(); i++)
				{
					cout << "\n" << i + 1 << ". " << users[i].get_surname() << ", age: " << users[i].get_age();
				}

				int chooseUser{};
				// checking chooseUser validity
				while (true)
				{
					cout << "\nCreate new profile or enter number: ";

					if (isInputInt(chooseUser) == true) // if inputted value isInt
					{
						if (chooseUser == -1) { break; } // user wants to exit
						else if (chooseUser == 0) { break; } // user wants to create new profile
						else if (isInRange(1, users.size(), chooseUser) == true) { break; } // if inputted value isInRange
					}
				}

				// user wants to exit
				if (chooseUser == -1) {}

				// user wants to create new profile
				else if (chooseUser == 0)
				{
					cout << "\nPlease enter your name and surname: "; string surname{};

					// ta linijka wczytuje whitespace'y
					cin >> ws;  getline(cin, surname);

					int age{};
					// checking age validity
					while (true)
					{
						cout << "\nAnd now your age: ";

						if (isInputInt(age) == true) // if inputted value isInt
						{
							if (age == -1) { break; } // user wants to exit
							else if (isInRange(6, 99, age) == true) { break; } // if inputted value isInRange
						}
					}

					if (age == -1) {} // user wants to exit

					else
					{
						User user(surname, age);  // creating user object									

						// if we haven't initialize week we do that here
						if (wereTracksInitialized(false) == false)
						{
							cout << "\nWait a second, we are cleaning cinema for you ;).\n";
							if (wereMoviesInitialized(false) == false) { movieSetter(); } // if we haven't initialize movies we do that here
							if (wereRoomsInitialized(false) == false) { roomSetter(); } // if we haven't initialize rooms we do that here

							trackSetter(); loadRoomsIntoTracks(); // if we haven't initialize tracks we do that here
							regenerateWeek(); // randomly filling tracks with movies
						}

						users.push_back(user);
						clientMenu(users.back());
					}
				}

				// user chose already existing client's profile
				else
				{
					clientMenu(users[chooseUser - 1]);
				}

			}

			// there are no client profiles
			else
			{
				cout << "Please enter your name and surname: "; string surname{};
				// ta linijka wczytuje whitespace'y
				cin >> ws;  getline(cin, surname);

				int age{};
				// checking age validity
				while (true)
				{
					cout << "\nAnd now your age: ";

					if (isInputInt(age) == true) // if inputted value isInt
					{
						if (age == -1) { break; } // user wants to exit
						else if (isInRange(6, 99, age) == true) { break; } // if inputted value isInRange
					}
				}

				if (age == -1) {} // user wants to exit

				else
				{
					User user(surname, age);  // creating user object									

					// if we haven't initialize week we do that here
					if (wereTracksInitialized(false) == false)
					{
						cout << "\nWait a second, we are cleaning cinema for you ;).\n";
						if (wereMoviesInitialized(false) == false) { movieSetter(); } // if we haven't initialize movies we do that here
						if (wereRoomsInitialized(false) == false) { roomSetter(); } // if we haven't initialize rooms we do that here

						trackSetter(); loadRoomsIntoTracks(); // if we haven't initialize tracks we do that here
						regenerateWeek(); // randomly filling tracks with movies
					}

					users.push_back(user);
					clientMenu(users[0]);
				}

			}

		} // user chose to be a client

		// user chose to be cinemaManager
		else if (roleChoose == 2)
		{
			managerMenu();
		} // user chose to be cinemaManager

	} // first while end
} // ,,start,, method end