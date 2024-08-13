/*Program for creatingand manipulating dates.*/

#include <iostream>
using namespace std;

struct Date {
	int y, m, d;				// year, month, day
	Date(int y, int m, int d);	// check for valid date and initialize
	void add_day(int n);		// increase the Date by n days
	void incr_day();			// increment the date by 1 day
	void incr_month();			// increment the date by 1 month
	void incr_year();			// increment the date by 1 year
};

// Helper functions:
class InvalidDate {};    // for throwing exceptions

bool is_leapyear(int y)	// Check if a year is a leapyear or not
{
	if (y % 4 != 0) return false;
	if (y % 100 == 0 && y % 400 != 0) return false;
	return true;
}

Date::Date(int yy, int mm, int dd)	// Check the provided date values are valid and if so, use them to intitialise the date dd
{
	if (yy < 1) throw InvalidDate{};							// check year, only restriction is that it be positive

	switch (mm) {                                               // check month and day
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:   // months with 31 days
		if (dd < 1 || dd > 31) throw InvalidDate{};
		break;
	case 4: case 6: case 9: case 11:                            // months with 30 days
		if (dd < 1 || dd > 30) throw InvalidDate{};
		break;
	case 2:														// february
		if (is_leapyear(yy)) {
			if (dd < 1 || dd > 29) throw InvalidDate{};
		}
		else if (dd < 1 || dd > 28) throw InvalidDate{};
		break;
	default:													// invalid month (not 1-12)
		throw InvalidDate{};
		break;
	}

	y = yy;														// date is valid, so initialise the date
	m = mm;
	d = dd;
}

void Date::incr_year() { ++y; }	// Increment date by a year

void Date::incr_month()	// Increment date by a month
{
	if (m == 12) {	// if last month of the year, roll back around to jan
		m = 1;
		incr_year();
	}
	else ++m;
}

void Date::incr_day()   // Increment date by a day
{
	bool is_last_day{ false };

	switch (m) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:   // months with 31 days
		if (d == 31) is_last_day = true;
		break;
	case 4: case 6: case 9: case 11:                            // months with 30 days
		if (d == 30) is_last_day = true;
		break;
	case 2:														// february
		if (is_leapyear(y)) {
			if (d == 29) is_last_day = true;
		}
		else if (d == 28) is_last_day = true;
		break;
	}

	if (is_last_day) {											// if last day of the month, roll back around to 1st
		d = 1;
		incr_month();
	}
	else ++d;
}

void Date::add_day(int n)   // Increase date by n days
{
	// the 2 first blocks of code here exist to speed up the function when very large numbers of days need adding

	if (m == 2 && d == 29) {												// special case if start on Feb 29th, since the day needs adjusting
		n -= 1;
		incr_day();
	}

	while (n >= 366) {														// increment years until there aren't enough days left to form one
		if ((m <= 2 && is_leapyear(y)) || (m > 2 && is_leapyear(y + 1))) {	// if there is a leapday between now and the same day next year
			n -= 366;
			incr_year();
		}
		else {
			n -= 365;
			incr_year();
		}
	}

	for (int i = 0; i < n; ++i) incr_day();									// add remaining days one at a time
}

ostream& operator<<(ostream& os, const Date& d)	// Operator for outputting a date
{
	return os << '(' << d.y
		<< ',' << int(d.m)
		<< ',' << d.d << ')';
}

int main()
try {
	Date today{ 1978, 6, 25 };					// a Date variable (a named object)

	Date tomorrow{ today };						// start off with today's date
	tomorrow.add_day(1);						// increase by 1 to get to tomorrow

	cout << today << endl << tomorrow << endl;
}
catch (InvalidDate) {
	cerr << "error: invalid date" << endl;
	return 1;
}