#include "year.h"
#include "..\..\std_lib_facilities.h"
using namespace std;

istream& operator>>(istream& is, Year& y)
// read a year from is into y
// format: { year 1972 . . . }
{
	char ch;
	is >> ch;
	if (ch != '{') {
		is.unget();
		is.clear(ios::failbit);
		return is;
	}
	string year_marker;
	int yy;
	is >> year_marker >> yy;
	if (!is || year_marker != "year") error("bad start of year");
	y.year = yy;
	while (true) {
		Month m;            // get a clean m each time around
		if (!(is >> m)) break;
		y.month[m.month] = m;
	}
	end_of_loop(is, '}', "bad end of year");
	return is;
}

void print_year(ofstream& ofs, const Year& y)
{
	ofs << "Year " << y.year << '\n';
	for (const Month& m : y.month)		// every month in the year
		if (m.month != not_a_month) {
			ofs << '\t';
			print_month(ofs, m);
		}
}