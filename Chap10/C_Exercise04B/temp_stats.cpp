/*Reads a file of temperature readings (with different units) and their hour in the day, calculates the mean and median.*/

#include <fstream>
#include <algorithm>
#include "..\..\std_lib_facilities.h"
using namespace std;

// Forward Declarations:
double ctof(const double);

struct Reading {	// A temperature reading
	Reading() {};
	Reading(int h, double t, char u) { set_hour(h); set_temp(t, u); }
	int get_hour() const { return hour; }
	double get_temp() const { return temperature; }
	char get_unit() const { return unit; }
	void set_hour(const int h)
	{
		if (0 > h || h > 23) error("Reading::set_hour(const int): invalid hour");	// pre
		hour = h;
	}
	void set_temp(const double t, const char u)
	{
		constexpr double abs0f{ -459.67 };											// lowest possible temperature value in Fahrenheit
		switch (u) {																// pre: must be valid temperature/unit
		case 'F': 
			if (t < abs0f) error("Reading::set_temp(const double): temp too low");
			break;
		case 'C':
			if (ctof(t) < abs0f) error("Reading::set_temp(const double): temp too low");
			break;
		default:
			error("Reading::set_temp(const double): unknown unit");
			break;
		}

		temperature = t;
		unit = u;
	}

private:
	int hour{ 0 };															// hour after midnight [0:23]
	double temperature{ 0. };
	char unit{ 'F' };														// 'F' for Fahrenheit, 'C' for Celsius
};
// Reading Helper Functions:
ifstream& operator>>(ifstream& ifs, Reading& r)	// Input readings from file
{
	int hour;
	double temp;
	char unit;
	int i; char c1, c2, c3;									// formatting numbers and characters
	

	ifs >> hour >> c1 >> i >> c2 >> temp >> c3 >> unit;		// e.g. 04:00, 8°F
	if (!ifs.good()) return ifs;							// avoids attempting to read uninitialised formatting variables

	if (c1 != ':' || i != 00 || c2 != ',' || c3 != '°') {	// check formatting
		ifs.clear(ios_base::failbit);
		return ifs;
	}
	ifs.peek();												// set eof flag if its the next character (necessary because the final thing we attempted
															// to read was a single char which doesn't trip the eof like reading an int/string would)
	r = Reading(hour, temp, unit);							// protections built into Reading struct will check validity of data
	return ifs;
}
double ctof(const double c)	// Convert a temp in Celsius to Fahrenheit
{
	return c * 9 / 5 + 32;	// formula
}
double median_ftemp(const vector<Reading>& readings)	// Calculate median temperature in Fahrenheit
{
	if (readings.size() == 0) error("error: median_temp(const vector<Reading>&): received empty vector");	// pre
	vector<double> ftemps;																					// extricate just the temperatures
	for (const Reading& r : readings) {																		// convert to Fahrenheit if needed
		switch (r.get_unit()) {
		case 'F': ftemps.push_back(r.get_temp());
			break;
		case 'C': ftemps.push_back(ctof(r.get_temp()));
			break;
		default: error("error: median_temp(const vector<Reading>&): reading with unknown unit");
			break;
		}
	}

	sort(ftemps);
	double low_median{ ftemps[(ftemps.size() - 1) / 2] };
	double high_median{ ftemps[ftemps.size() / 2] };
	double median{ (low_median + high_median) / 2 };
	return median;
}
ostream& operator<<(ostream& os, const Reading& r)	// Output readings to file
{
	if (r.get_hour() < 10) os << 0;									// add a leading zero if needed
	os << r.get_hour() << ":00, " << r.get_temp() << '°' << r.get_unit();
	return os;
}

int main()
try {
	string filename{ "..\\C_Exercise04A\\raw_temps.txt" };						// double backslash to avoid escaping
	ifstream ifs{ filename };													// create file input stream and open file
	if (!ifs) error("error: main(): failed to open file ", filename);

	vector<Reading> readings;
	double tsum{ 0 };
	while (ifs.good()) {														// loop while istream has no flags set
		Reading r;
		if (ifs >> r) {
			switch (r.get_unit()) {												// convert temps to Fahrenheit if needed
			case 'F': break;
			case 'C': r.set_temp(ctof(r.get_temp()), 'F'); break;
			default: error("error: main(): unknown unit");
			}
			readings.push_back(r);
			tsum += r.get_temp();
		}
	}
	if (ifs.bad()) error("error: main(): could not read ", filename);
	else if (ifs.fail()) error("error: main(): invalid input from ", filename);
	else if (ifs.eof()) ifs.clear();											// success, eof reached, clear istream flag for reuse

	double mean{ tsum / readings.size() };
	double median{ median_ftemp(readings) };

	cout << "Mean Temp: " << mean << endl << "Median Temp: " << median << endl;
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}