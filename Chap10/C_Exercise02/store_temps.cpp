/*Creates a file of temperature readings and their time of day.*/

#include <fstream>
#include "..\..\std_lib_facilities.h"
using namespace std;

struct Reading {	// A temperature reading
	int hour;			// hour after midnight [0:23]
	double temperature;	// in Fahrenheit
};
// Reading Helper Functions:
ofstream& operator<<(ofstream& ofs, const Reading& r)	// Output readings to file
{
	if (r.hour < 10) ofs << 0;							// add a leading zero if needed
	ofs << r.hour << ":00, " << r.temperature << "°F";
	return ofs;
}

int main()
try {
	string filename{ "raw_temps.txt" };
	ofstream ofs{ filename };											// create file output stream and open file
	if (!ofs) error("error: main(): failed to open file ", filename);

	vector<Reading> readings;											// create some test readings
	for (int i = 0; i < 50; ++i) {
		readings.push_back(Reading());
		readings[i].hour = i % 24;
		readings[i].temperature = i * 2;
	}

	for (int i = 0; i < readings.size(); ++i) {							// write readings to file
		ofs << readings[i];
		if (i < readings.size() - 1) ofs << endl;						// omit newline at the end
	}
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}