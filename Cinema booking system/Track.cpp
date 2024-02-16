#include "Track.h"

// Implementation of the addRoom method
void Track::addRoom(Room room)
{
    // Create a Day object for the room
    Day pokoj;
    // Add the room to the 'rooms' map and initialize its schedule in 'roomTracks'
    rooms[room.get_number()] = room;
    roomTracks[room.get_number()] = pokoj;
    // Set the initial opening and closing events for the cinema
    roomTracks[room.get_number()].setEvent("CINEMA CLOSED", 0, 0, openHour, openMin, false);
    roomTracks[room.get_number()].setEvent("CINEMA CLOSED", closeHour, closeMin, 23, 59, false);
}

// Implementation of the setMovie method
bool Track::setMovie(Room room, Movie movie, int eventStartHour, int eventStartMin, bool inform)
{
    int roomNumber = room.get_number();
    int searchStart = eventStartHour * 60 + eventStartMin; // Convert start time to minutes
    Minute minDefault{};

    // Check if the event start time is correct
    if (checkIsTimeCorrect(eventStartHour, eventStartMin, false) == false)
    {
        cout << "\n***ERROR: Can't set movie in this period. Event start time values are incorrect.***\n";
        return false;
    }
    // Check if the movie is set before opening
    else if (openHour > eventStartHour || (openHour == eventStartHour && openMin + 5 > eventStartMin))
    {
        if (inform == true)
        {
            cout << "\n***ERROR: Can't set movie before opening. Choose another period. \nRemember that the earliest you can set a movie is 5 minutes after opening.***\n";
        }
        return false;
    }
    // Check if there is a movie scheduled within the required time
    else if (roomTracks[roomNumber].get_time()[searchStart - 5].get_byWhat() != minDefault.get_byWhat())
    {
        int eventEndMin, eventEndHour{};
        addTimes(eventStartHour, eventStartMin, movie.get_hours(), movie.get_minutes(), eventEndHour, eventEndMin); // Set the end time of the event

        if (inform == true)
        {
            cout << "\nTrying to set this event: " << movie.get_name() << ", ";
            preetyHours(eventStartHour, eventStartMin, eventEndHour, eventEndMin);
        }

        if (inform == true)
        {
            cout << "***ERROR: Can't set the movie.\nRemember that the earliest you can set a movie is 5 minutes after another movie. Information below:";
            roomTracks[roomNumber].findEventLength(searchStart - 5);
        }
        return false;
    }
    else
    {
        // If conditions are met, set the movie in the specified time
        int eventEndMin, eventEndHour{};
        addTimes(eventStartHour, eventStartMin, movie.get_hours(), movie.get_minutes(), eventEndHour, eventEndMin);

        if (roomTracks[roomNumber].setEvent(movie.get_name(), eventStartHour, eventStartMin, eventEndHour, eventEndMin, inform) == true)
        {
            // Update the seat matrix and return success
            rooms[roomNumber].newSeatMatrix(eventStartHour, eventStartMin, eventEndHour, eventEndMin);
            rooms[roomNumber].randomlyTakeSeats(eventStartHour, eventStartMin, eventEndHour, eventEndMin);
            return true;
        }
        return true;
    }
}

// Implementation of the deleteMovie method
void Track::deleteMovie(Room room, Movie movie, int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin, bool inform)
{
    // Check if the event start and end times are correct
    if (checkIsTimeCorrect(eventStartHour, eventStartMin, false) == false)
    {
        cout << "\n***ERROR: Can't set movie in this period. Event start time values are incorrect.***\n";
    }
    else if (checkIsTimeCorrect(eventEndHour, eventEndMin, false) == false)
    {
        cout << "\n***ERROR: Can't set movie in this period. Event end time values are incorrect.***\n";
    }
    else
    {
        int roomNumber = room.get_number();
        // Delete the movie event from the schedule and update the seat matrix
        roomTracks[roomNumber].deleteEvent(movie.get_name(), eventStartHour, eventStartMin, eventEndHour, eventEndMin, inform);
        rooms[roomNumber].deleteSeatMatrix(eventStartHour, eventStartMin, eventEndHour, eventEndMin);
    }
}

// Implementation of the changeMovieHours method
void Track::changeMovieHours(Room room, Movie movie, int newEventStartHour, int newEventStartMin, int oldEventStartHour, int oldEventStartMin)
{
    int roomNumber = room.get_number();
    int searchStart = newEventStartHour * 60 + newEventStartMin;
    Minute minDefault{};

    // Check if the event start times are correct
    if (checkIsTimeCorrect(newEventStartHour, newEventStartMin, false) == false || checkIsTimeCorrect(oldEventStartHour, oldEventStartMin, false) == false)
    {
        cout << "\n***ERROR: Can't set movie in this period. Event start time values are incorrect.***\n";
    }
    else
    {
        int oldEventStart, oldEventEnd;
        // Get the start and end times of the old movie event
        roomTracks[roomNumber].getEventLength(movie.get_name(), oldEventStart, oldEventEnd, oldEventStartHour, oldEventStartMin);

        int oldEventEndHour, oldEventEndMin;
        minToPeriod(oldEventStart, oldEventEnd, oldEventStartHour, oldEventStartMin, oldEventEndHour, oldEventEndMin);

        int newEventEndMin, newEventEndHour{};
        addTimes(newEventStartHour, newEventStartMin, movie.get_hours(), movie.get_minutes(), newEventEndHour, newEventEndMin);

        cout << "\nTrying to change movie \"" << movie.get_name() << "\" hours from ";
        preetyHours(oldEventStartHour, oldEventStartMin, oldEventEndHour, oldEventEndMin, false);
        cout << " to ";
        preetyHours(newEventStartHour, newEventStartMin, newEventEndHour, newEventEndMin);

        // Delete the old movie event and set the movie with new hours
        deleteMovie(room, movie, oldEventStartHour, oldEventStartMin, oldEventEndHour, oldEventEndMin, false);
        if (setMovie(room, movie, newEventStartHour, newEventStartMin, false) == true)
        {
            cout << "Movie's hours were successfully changed." << endl;
            // Update the seat matrix hours
            rooms[roomNumber].changeSeatMatrixHours(oldEventStartHour, oldEventStartMin, oldEventEndHour, oldEventEndMin,
                newEventStartHour, newEventStartMin, newEventEndHour, newEventEndMin);
        }
        else
        {
            setMovie(room, movie, oldEventStartHour, oldEventStartMin, false);
        }
    }
}

// Implementation of the showRoomSchedule method
void Track::showRoomSchedule(Room room, int eventStartHour, int eventStartMin, int eventEndHour, int eventEndMin)
{
    // Check if the event start and end times are correct
    if (checkIsTimeCorrect(eventStartHour, eventStartMin, false) == false)
    {
        cout << "\n***ERROR: Can't show room's schedule in this period. Event start time values are incorrect.***\n";
    }
    else if (checkIsTimeCorrect(eventEndHour, eventEndMin, false) == false)
    {
        cout << "\n***ERROR: Can't show room's schedule in this period. Event end time values are incorrect.***\n";
    }
    else
    {
        int roomNumber = room.get_number();
        string can3D;
        // Check if the room supports 3D
        if (room.get_display3D() == true)
        {
            can3D = "2D/3D";
            cout << "\n      " << can3D << " ROOM " << roomNumber + 1;
        }
        else
        {
            can3D = "2D";
            cout << "\n       " << can3D << " ROOM " << roomNumber + 1;
        }

        // Print out the room's schedule for the specified time
        roomTracks[roomNumber].printOut(eventStartHour, eventStartMin, eventEndHour, eventEndMin);
    }
}

// Implementation of the resetRoomSchedule method
void Track::resetRoomSchedule(Room room, bool inform)
{
    int roomNumber = room.get_number();
    // Reset the room's schedule and set opening and closing events
    roomTracks[roomNumber].reset(inform);
    roomTracks[roomNumber].setEvent("CINEMA CLOSED", 0, 0, openHour, openMin, false);
    roomTracks[roomNumber].setEvent("CINEMA CLOSED", closeHour, closeMin, 23, 59, false);
}

// Implementation of the showTodaysSchedule method
void Track::showTodaysSchedule(bool startText)
{
    if (startText == true)
    {
        cout << "\nShowing day's schedule: " << endl;
    }

    // Print out the schedule for each room
    for (int i = 0; i < rooms.size(); i++)
    {
        showRoomSchedule(rooms[i]);
    }

    cout << "\nThat's all for this day." << endl;
}

// Implementation of the resetTodaysSchedule method
void Track::resetTodaysSchedule(bool inform)
{
    if (inform == true)
    {
        cout << "\nResetting today's schedule..." << endl;
    }

    // Reset the schedule for each room
    for (int i = 0; i < rooms.size(); i++)
    {
        resetRoomSchedule(rooms[i], false);
    }

    if (inform == true)
    {
        cout << "Done - it's all clear." << endl;
    };
}

// Implementation of the searchForMovie method
map<vector<int>, vector<int>> Track::searchForMovie(Movie movie, bool wantStartText /*= true*/, bool numberSearched /*= false*/, int numberSearchedStart /*= 1*/)
{
    if (wantStartText == true)
    {
        cout << "\nSearching for movie: \"" << movie.get_name() << "\" in day's schedule." << endl;
    }

    // In vector1: roomNumber, iteration
    map<vector<int>, vector<int>> movies;
    // In vector2: eventStartHour, eventStartMin, eventEndHour, eventEndMin
    int movieLength = movie.get_hours() * 60 + movie.get_minutes(); // Duration of the movie in minutes
    int searchNumber = numberSearchedStart; // Number from which we will start printing out movies iteration

    // Iterate through all rooms
    for (int i = 0; i < rooms.size(); i++)
    {
        int roomNumber = rooms[i].get_number();
        int min = 0;        // It will control where we start searching, i.e., after the end of the first found movie
        int iteration = 0; // If we find the same movie again in the same room, iteration will show that it's the movie's second iteration

        // Continue searching until the end of the day
        while (true)
        {
            if (min > 1440 - movieLength) // If the movie lasts 100 minutes, and we are above 1340 minutes, then break
            {
                break;
            }
            else
            {
                int minStartHour = min / 60; int minStartMin = min % 60; // Convert minutes
                int eventStart, eventEnd{};
                // Find the start and end minute of the movie event
                roomTracks[i].getEventLength(movie.get_name(), eventStart, eventEnd, minStartHour, minStartMin, 24, 0);

                if (eventStart == 0 && eventEnd == 0) { break; } // getEventLength will return 0 if nothing is found

                int eventStartHour, eventStartMin, eventEndHour, eventEndMin{};
                // Convert minutes to hours
                minToPeriod(eventStart, eventEnd, eventStartHour, eventStartMin, eventEndHour, eventEndMin);

                // Assign movie information to the map
                movies.insert({ {roomNumber, iteration}, {eventStartHour, eventStartMin, eventEndHour, eventEndMin} });
                iteration = iteration + 1; // If we find the same movie again in the same room, the iteration will show that it's the movie's second iteration

                if (numberSearched == true) { cout << searchNumber << ".	"; }
                cout << "Room " << roomNumber + 1 << ", ";
                preetyHours(eventStartHour, eventStartMin, eventEndHour, eventEndMin, false); // Print out the found movie

                // Print additional information based on movie and room characteristics
                if (movie.get_PLdub() == true && movie.get_is3D() == true && rooms[i].get_display3D() == true) { cout << ", polish dubbing and subtitles, 3D \n"; }
                else if (movie.get_PLdub() == true && movie.get_is3D() == true && rooms[i].get_display3D() == false) { cout << ", polish dubbing and subtitles, 2D \n"; }
                else if (movie.get_PLdub() == true && movie.get_is3D() == false) { cout << ", polish dubbing and subtitles, 2D\n"; }
                else if (movie.get_PLdub() == false && movie.get_is3D() == true && rooms[i].get_display3D() == true) { cout << ", polish subtitles, 3D\n"; }
                else { cout << ", polish subtitles, 2D\n"; }

                searchNumber = searchNumber + 1; // The next search will have an incremented number
                min = eventEnd + 1; // Next time we will start searching a minute after the end of the movie
            }
        }
    }
    return movies; // Return the map with the movies and their timings
}