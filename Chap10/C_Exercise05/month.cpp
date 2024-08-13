#include "month.h"
#include "..\..\std_lib_facilities.h"
using namespace std;

// Month Helper Functions:
vector<string> month_input_tbl = {
		   "jan", "feb", "mar", "apr", "may", "jun", "jul",
		   "aug", "sep", "oct", "nov", "dec"
};

int month_to_int(string s)
// is s the name of a month? If so return its index [0:11] otherwise –1
{
	for (int i = 0; i < 12; ++i) if (month_input_tbl[i] == s) return i;
	return -1;
}

istream& operator>>(istream& is, Month& m)
// read a month from is into m
// format: { month feb . . . }
{
	char ch = 0;
	if (is >> ch && ch != '{') {
		is.unget();
		is.clear(ios_base::failbit);                  // we failed to read a Month
		return is;
	}
	string month_marker;
	string mm;
	is >> month_marker >> mm;
	if (!is || month_marker != "month") error("bad start of month");
	m.month = month_to_int(mm);
	int duplicates = 0;
	int invalids = 0;
	for (Reading r; is >> r; ) {
		if (is_valid(r)) {
			if (m.day[r.day].hour[r.hour] != not_a_reading)
				++duplicates;
			m.day[r.day].hour[r.hour] = r.temperature;
		}
		else
			++invalids;
	}
	if (invalids) error("invalid readings in month", invalids);
	if (duplicates) error("duplicate readings in month", duplicates);
	end_of_loop(is, '}', "bad end of month");
	return is;
}

void end_of_loop(istream& ist, char term, const string& message)
// check for failed read indicating the end of a read loop, if found check for terminating
// character. throw error message if there's a failed read but no terminating character
{
	if (ist.fail()) {                // use term as terminator and/or separator
		ist.clear();
		char ch;
		if (ist >> ch && ch == term) return;             // all is fine
		error(message);
	}
}

vector<string> month_print_tbl = {
		  "January", "February", "March", "April", "May", "June", "July",
		  "August", "September", "October", "November", "December"
};

string int_to_month(int i)
// months [0:11]
{
	if (i < 0 || 12 <= i) error("bad month index");
	return month_print_tbl[i];
}

void print_month(ofstream& ofs, const Month& m)
{
	ofs << int_to_month(m.month) << '\n';

	for (int i = 0; i < m.day.size(); ++i) {								// every day in the month
		for (const double h : m.day[i].hour)								// every hour in the day
			if (h != not_a_reading) {										// only print the day if theres a reading for one of its hours
				ofs << "\t\t" << "Day " << i << '\n';
				print_day(ofs, m.day[i]);
				break;
			}
	}
}