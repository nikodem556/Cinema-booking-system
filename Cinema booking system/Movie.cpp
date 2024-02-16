#include "Movie.h"
using namespace std;
#include <iostream>

// Implementation of info method
void Movie::info()
{
	int hours = get_hours(); int mins = get_minutes();
	cout << "\n		\"" << get_name() << "\"	" << "\nGenre: " << get_genre() << ", length: ";
	if (mins < 10) { cout << hours << ":0" << mins << endl; }
	else { cout << hours << ":" << mins << endl; }
	cout << "Required age: " << get_minAge() << "+,";
	if (get_PLdub() == true && get_is3D() == true) { cout << " has polish dubbing and subtitles, 3D available\n"; }
	else if (get_PLdub() == true && get_is3D() == false) { cout << " has polish dubbing and subtitles, 3D unavailable\n"; }
	else if (get_PLdub() == false && get_is3D() == true) { cout << " only polish subtitles, 3D available\n"; }
	else { cout << " only polish subtitles, 3D unavailable\n"; }
}


