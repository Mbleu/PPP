/*Reads a file of temperature readings and their hour in the day, calculates the mean and median.*/

#include <fstream>
#include <algorithm>
#include "..\..\std_lib_facilities.h"
using namespace std;

struct Reading {	// A temperature reading
	int hour;			// hour after midnight [0:23]
	double temperature;	// in Fahrenheit
};
// Reading Helper Functions:
ifstream& operator>>(ifstream& ifs, Reading& r)	// Input readings from file
{
	int hour;
	double temp;
	int i; char c1, c2, c3, c4;												// formatting numbers and characters
	constexpr double abs0f{ -459.67 };										// lowest possible temperature value

	ifs >> hour >> c1 >> i >> c2 >> temp >> c3 >> c4;						// e.g. 04:00, 8°F
	if (!ifs.good()) return ifs;											// avoids attempting to read uninitialised formatting variables
	if (0 > hour || hour > 23 || temp < abs0f								// check validity of data
		|| c1 != ':' || i != 00 || c2 != ',' || c3 != '°' || c4 != 'F') {	// check formatting
		ifs.clear(ios_base::failbit);
		return ifs;
	}
	ifs.peek();																// set eof flag if its the next character (necessary because the final thing we attempted
																			// to read was a single char which doesn't trip the eof like reading an int/string would)
	r.hour = hour;
	r.temperature = temp;
	return ifs;
}
double median_temp(const vector<Reading>& readings)
{
	if (readings.size() == 0) error("error: median_temp(const vector<Reading>&): received empty vector");	// pre
	vector<double> temps;																					// extricate just the temperatures
	for (const Reading& r : readings)
		temps.push_back(r.temperature);

	sort(temps);
	double low_median{ temps[(temps.size() - 1) / 2] };
	double high_median{ temps[temps.size() / 2]};
	double median{ (low_median + high_median) / 2 };
	return median;
}

int main()
try {
	string filename{ "..\\C_Exercise02\\raw_temps.txt" };						// double backslash to avoid escaping
	ifstream ifs{ filename };													// create file input stream and open file
	if (!ifs) error("error: main(): failed to open file ", filename);

	vector<Reading> readings;
	double tsum{ 0 };
	while (ifs.good()) {														// loop while istream has no flags set
		Reading r;
		if (ifs >> r) {
			readings.push_back(r);
			tsum += r.temperature;
		}
	}
	if (ifs.bad()) error("error: main(): could not read ", filename);
	else if (ifs.fail()) error("error: main(): invalid input from ", filename);
	else if (ifs.eof()) ifs.clear();											// success, eof reached, clear istream flag for reuse

	double mean{ tsum / readings.size() };
	double median{ median_temp(readings) };

	cout << "Mean Temp: " << mean << endl << "Median Temp: " << median << endl;
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}