#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Day.h"
#include "Room.h"
#include "Movie.h"
#include "Time.h"

using namespace std;

// Track is like a week's day, f.e Monday or Tuesday
class Track : private Time 
{
private:
    map<int, Room> rooms{};     // rooms avaiable in this cinema day
    map<int, Day> roomTracks{}; // rooms' schedules
    int openHour, openMin;
    int closeHour, closeMin;

public:
    // Constructor to set default opening and closing times
    Track(int m_openHour = 13, int m_openMin = 0, int m_closeHour = 23, int m_closeMin = 0) : openHour{ m_openHour }, openMin{ m_openMin }, closeHour{ m_closeHour }, closeMin{ m_closeMin } {}

    // Getters
    map<int, Room> get_rooms(void) const { return rooms; }
    map<int, Day> get_roomTracks(void) const { return roomTracks; }
    int get_openTime(void) const { return openHour * 60 + openMin; }
    int get_closeTime(void) const { return closeHour * 60 + closeMin; }

    // Setter
    void set_rooms(map<int, Room> m_rooms) { rooms = m_rooms; }

    // Add room to track
    void addRoom(Room room);
    
    // Set movie in the described time
    bool setMovie(Room room, Movie movie, int eventStartHour, int eventStartMin, bool inform = true);
    
    // Delete movie in the described time (by default, it searches for the earliest one and deletes the whole event)
    void deleteMovie(Room room, Movie movie, int eventStartHour = 0, int eventStartMin = 0, int eventEndHour = 24, int eventEndMin = 0, bool inform = true);
   
    // Change movie hours to newEventStart
    void changeMovieHours(Room room, Movie movie, int newEventStartHour, int newEventStartMin, int oldEventStartHour = 0, int oldEventStartMin = 0);
    
    // Show the current room schedule in the described time (by default - whole day)
    void showRoomSchedule(Room room, int eventStartHour = 0, int eventStartMin = 0, int eventEndHour = 24, int eventEndMin = 0);

    // Reset the room's schedule
    void resetRoomSchedule(Room room, bool inform = true);
   
    // Show track schedule
    void showTodaysSchedule(bool startText = true);
   
    // Reset track schedule
    void resetTodaysSchedule(bool inform = true);

    // Print out when and where the described movie is playing (wantStartText - inform which movie it's searching, NumberSearched - adds ,numberSearchedStart., numberSearchedStart+1., at the start of every find iteration)
    map<vector<int>, vector<int>> searchForMovie(Movie movie, bool wantStartText = true, bool numberSearched = false, int numberSearchedStart = 1);
};
 
