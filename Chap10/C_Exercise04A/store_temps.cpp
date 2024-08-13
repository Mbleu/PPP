/*Creates a file of temperature readings (with different units) and their time of day.*/

#include <fstream>
#include "..\..\std_lib_facilities.h"
using namespace std;

struct Reading {	// A temperature reading
	Reading() {};
	Reading(int h, double t, char u) : hour(h), temperature(t), unit(u) {}
	int hour{ 0 };															// hour after midnight [0:23]
	double temperature{ 0. };
	char unit{ 'F' };														// 'F' for Fahrenheit, 'C' for Celsius
};
// Reading Helper Functions:
ofstream& operator<<(ofstream& ofs, const Reading& r)	// Output readings to file
{
	if (r.hour < 10) ofs << 0;									// add a leading zero if needed
	ofs << r.hour << ":00, " << r.temperature << '°' << r.unit;
	return ofs;
}

int main()
try {
	string filename{ "raw_temps.txt" };
	ofstream ofs{ filename };											// create file output stream and open file
	if (!ofs) error("error: main(): failed to open file ", filename);

	vector<Reading> readings;											// create some test readings with arbitrary varied values
	for (int i = 0; i < 50; ++i) {
		int hour{ i % 24 };
		double temperature{ i * 2. };
		char unit{ 'F' };
		if (i % 2 == 0) unit = 'C';
		readings.push_back(Reading(hour, temperature, unit));
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