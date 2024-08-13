#include "reading.h"
#include "..\..\std_lib_facilities.h"
using namespace std;

// Reading Helper Functions:
bool is_valid(const Reading& r)
// a rough test
{
	if (r.day < 1 || 31 < r.day) return false;
	if (r.hour < 0 || 23 < r.hour) return false;
	if (r.temperature < implausible_min || implausible_max < r.temperature)
		return false;
	return true;
}

istream& operator>>(istream& is, Reading& r)
// read a temperature reading from is into r
// format: ( 3 4 9.7 )
// check format, but don’t bother with data validity
{
	char ch1;
	if (is >> ch1 && ch1 != '(') {                                // could it be a Reading?
		is.unget();
		is.clear(ios_base::failbit);
		return is;
	}
	char ch2;
	int d;
	int h;
	double t;
	is >> d >> h >> t >> ch2;
	if (!is || ch2 != ')') error("bad reading");      // messed-up reading
	r.day = d;
	r.hour = h;
	r.temperature = t;
	return is;
}