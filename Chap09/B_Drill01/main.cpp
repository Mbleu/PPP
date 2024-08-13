/*Program for creatingand manipulating dates.*/

#include <iostream>
using namespace std;

struct Date {
    int y;	// year
    int m;	// month in year
    int d;	// day of month
};

// Helper functions:
class InvalidDate{};    // for throwing exceptions

bool is_leapyear(int y) // Check if a year is a leapyear or not
{
    if (y % 4 != 0) return false;
    if (y % 100 == 0 && y % 400 != 0) return false;
    return true;
}

void init_day(Date& dd, int y, int m, int d)    // Check the provided date values are valid and if so, use them to intitialise the date dd
{
    if (y < 1) throw InvalidDate{};								// check year, only restriction is that it be positive

    switch (m) {                                                // check month and day
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:   // months with 31 days
        if (d < 1 || d > 31) throw InvalidDate{};
        break;
    case 4: case 6: case 9: case 11:                            // months with 30 days
        if (d < 1 || d > 30) throw InvalidDate{};
        break;
    case 2:														// february
		if (is_leapyear(y)) {
			if (d < 1 || d > 29) throw InvalidDate{};
		}  
        else if (d < 1 || d > 28) throw InvalidDate{};
        break;
	default:													// invalid month (not 1-12)
		throw InvalidDate{};
		break;
    }

	dd.y = y;													// date is valid, so initialise the date
	dd.m = m;
	dd.d = d;
}

void incr_year(Date& dd) { ++dd.y; }	// Increment date by a year

void incr_month(Date& dd)	// Increment date by a month
{
	if (dd.m == 12) {		// if last month of the year, roll back around to jan
		dd.m = 1;
		incr_year(dd);
	}
	else ++dd.m;
}

void incr_day(Date& dd)   // Increment date by a day
{
	bool is_last_day{ false };

	switch (dd.m) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:   // months with 31 days
		if (dd.d == 31) is_last_day = true;
		break;
	case 4: case 6: case 9: case 11:                            // months with 30 days
		if (dd.d == 30) is_last_day = true;
		break;
	case 2:														// february
		if (is_leapyear(dd.y)) {
			if (dd.d == 29) is_last_day = true;
		}
		else if (dd.d == 28) is_last_day = true;
		break;
	}

	if (is_last_day) {											// if last day of the month, roll back around to 1st
		dd.d = 1;
		incr_month(dd);
	}
	else ++dd.d;
}

void add_day(Date& dd, int n)   // Increase date by n days
{
	// the 2 first blocks of code here exist to speed up the function when very large numbers of days need adding

	if (dd.m == 2 && dd.d == 29) {														// special case if start on Feb 29th, since the day needs adjusting
		n -= 1;
		incr_day(dd);
	}

	while (n >= 366) {																	// increment years until there aren't enough days left to form one
		if ((dd.m <= 2 && is_leapyear(dd.y)) || (dd.m > 2 && is_leapyear(dd.y + 1))) {	// if there is a leapday between now and the same day next year
			n -= 366;
			incr_year(dd);
		}
		else {
			n -= 365;
			incr_year(dd);
		}
	}

	for (int i = 0; i < n; ++i) incr_day(dd);											// add remaining days one at a time
}

ostream& operator<<(ostream& os, const Date& d)	// Operator for outputting a date
{
	return os << '(' << d.y
		<< ',' << int(d.m)
		<< ',' << d.d << ')';
}

int main()
try {
    Date today;									// a Date variable (a named object)
    init_day(today, 1978, 6, 25);				// example day

    Date tomorrow{today};						// start off with today's date
    add_day(tomorrow, 1);						// increase by 1 to get to tomorrow

	cout << today << endl << tomorrow << endl;
}
catch (InvalidDate) {
    cerr << "error: invalid date" << endl;
    return 1;
}