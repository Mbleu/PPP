#include "day.h"
using namespace std;

// Day Helper Functions:
void print_day(ofstream& ofs, const Day& d)
{
	for (int i = 0; i < d.hour.size(); ++i) {				// every hour in the day
		if (d.hour[i] != not_a_reading) {					// print only the hours with readings
			ofs << "\t\t\t";
			if (i < 10) ofs << 0;							// add leading 0 if needed
			ofs << i << ":00 " << d.hour[i] << "°" << endl;
		}
	}
}