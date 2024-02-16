#include "User.h"
#include "Order.h"

// Implementation of the buyTicket method
void User::buyTicket(Track& track, Room room, string day, int row, int column,
    Movie movie, int startHour, int startMin, int endHour, int endMin, bool wantPLdub, bool want3D, string userSurname, int userAge)
{
    Order ticket;
    // If the ticket purchase is successful, add it to the User's list of tickets
    if (ticket.buyTicket(track, room, day, row, column, movie, startHour, startMin, endHour, endMin, wantPLdub, want3D, get_surname(), get_age()) == true)
    {
        tickets.push_back(ticket);
    }
}

// Implementation of the showTickets method
void User::showTickets()
{
    if (tickets.size() == 0) { cout << "\n***ERROR: You have no tickets.***\n"; }
    else
    { 
        cout << "\n **************************************";
        for (int i = 0; i < tickets.size(); i++)
        {
            cout << "\n\n		 TICKET " << i + 1 << "		";
            tickets[i].ticketInfo();
        }
        cout << "\n **************************************\n";
    }
}

// Implementation of the deleteTicket method
bool User::deleteTicket(vector<Track>& week, int ticketCode)
{
    int ticketPosition = -1;

    // Search for the ticket with the specified code in the User's list of tickets
    for (int t = 0; t < tickets.size(); t++)
    {
        if (tickets[t].get_Code() == ticketCode) { ticketPosition = t; break; }
    }

    // If the ticket with the specified code is not found
    if (ticketPosition == -1)
    {
        cout << "\n***ERROR: Entered ticket's CODE invalid.***";
        return false;
    }
    else
    {
        // Extract information from the ticket to free up the corresponding seat in the cinema
        vector<int> hours = tickets[ticketPosition].get_hours();
        vector<int> misc = tickets[ticketPosition].get_misc();
        vector<string> strings = tickets[ticketPosition].get_strings();
        int startHour = hours[0]; int startMin = hours[1]; int endHour = hours[2]; int endMin = hours[3];
        int row = misc[0]; int column = misc[1]; int roomNumber = misc[2] - 1;
        string day = strings[1]; int dayNumber = -1;
        vector<string> days{ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

        // Find the corresponding day in the cinema schedule
        for (int i = 0; i < days.size(); i++)
        {
            if (days[i] == day) { dayNumber = i; break; }
        }

        // If the day is not found in the schedule
        if (dayNumber == -1) { cout << "***ERROR: Invalid day name in ticket.***"; return false; };

        // Free up the seat in the cinema room
        map <int, Room> rooms = week[dayNumber].get_rooms();
        rooms[roomNumber].freeSeat(startHour, startMin, endHour, endMin, row, column);
        week[dayNumber].set_rooms(rooms);  // Update the cinema schedule with the freed seat

        // Remove the ticket from the User's list
        tickets.erase(tickets.begin() + ticketPosition);
        cout << "\nTicket was deleted.\n";

        return true;
    }
}
