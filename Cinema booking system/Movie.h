#pragma once
#include <ostream>

using namespace std;

class Movie
{
private:
	string fname, fgenre;
	int fhours, fminutes, fminAge;  // duration of the movie
	bool fPLdub, fis3D;  // Polish subtitles are default B))

public:
	// Constructor with parameters for movie details
	Movie(string name, string genre, int hours, int minutes, int minAge, bool PLdub, bool is3D)
		: fname{ name }, fgenre{ genre }, fhours{ hours }, fminutes{ minutes },
		fminAge{ minAge }, fPLdub{ PLdub }, fis3D{ is3D } {}

	// Getter methods
	string get_name(void) const { return fname; }
	string get_genre(void) const { return fgenre; }
	int get_hours(void) const { return fhours; }
	int get_minutes(void) const { return fminutes; }
	int get_minAge(void) const { return fminAge; }
	bool get_PLdub(void) const { return fPLdub; }
	bool get_is3D(void) const { return fis3D; }

	// Setter methods
	void set_minAge(int minAge) { fminAge = minAge; }
	void set_PLdub(bool PLdub) { fPLdub = PLdub; }
	void set_is3D(bool is3D) { fis3D = is3D; }

	// Method to display movie parameters
	void info();
};

