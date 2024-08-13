/*Program for creatingand manipulating dates.*/

#include <iostream>
using namespace std;

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
	Date(int y, Month m, int d);		// check for valid date and initialize

	void add_day(int n);				// increase the Date by n days
	void add_month(int n);				// increase the Date by n months
	void add_year(int n);				// increase the Date by n years

	void incr_day();					// increment the date by 1 day
	void incr_month();					// increment the date by 1 month
	void incr_year();					// increment the date by 1 year

	int day() const { return d; }
	Month month() const { return m; }
	int year() const { return y; }

private:
	int y;								// year
	Month m;							// month
	int d;								// day
};

// Helper functions:
class InvalidDate {};    // for throwing exceptions

bool is_leapyear(int y)	// Check if a year is a leapyear or not
{
	if (y % 4 != 0) return false;
	if (y % 100 == 0 && y % 400 != 0) return false;
	return true;
}

Date::Date(int yy, Month mm, int dd)	// Check the provided date values are valid and if so, use them to intitialise the date dd
{
	if (yy < 1) throw InvalidDate{};									// check year, only restriction is that it be positive

	switch (mm) {														// check month and day
	case Month::jan: case Month::mar: case Month::may: case Month::jul: // months with 31 days
	case Month::aug: case Month::oct: case Month::dec:
		if (dd < 1 || dd > 31) throw InvalidDate{};
		break;
	case Month::apr: case Month::jun: case Month::sep: case Month::nov:	// months with 30 days
		if (dd < 1 || dd > 30) throw InvalidDate{};
		break;
	case Month::feb:													// february
		if (is_leapyear(yy)) {
			if (dd < 1 || dd > 29) throw InvalidDate{};
		}
		else if (dd < 1 || dd > 28) throw InvalidDate{};
		break;
	default:															// invalid month (not jan-dec)
		throw InvalidDate{};
		break;
	}

	y = yy;																// date is valid, so initialise the date
	m = mm;
	d = dd;
}

void Date::incr_year() { ++y; }	// Increment date by a year

void Date::incr_month()	// Increment date by a month
{
	if (m == Month::dec) {		// if last month of the year, roll back around to jan
		m = Month::jan;
		incr_year();
	}
	else m = Month(int(m) + 1);
}

void Date::incr_day()   // Increment date by a day
{
	bool is_last_day{ false };

	switch (m) {
	case Month::jan: case Month::mar: case Month::may: case Month::jul:	// months with 31 days
	case Month::aug: case Month::oct: case Month::dec:
		if (d == 31) is_last_day = true;
		break;
	case Month::apr: case Month::jun: case Month::sep: case Month::nov:	// months with 30 days
		if (d == 30) is_last_day = true;
		break;
	case Month::feb:													// february
		if (is_leapyear(y)) {
			if (d == 29) is_last_day = true;
		}
		else if (d == 28) is_last_day = true;
		break;
	}

	if (is_last_day) {													// if last day of the month, roll back around to 1st
		d = 1;
		incr_month();
	}
	else ++d;
}

void Date::add_day(int n)   // Increase date by n days
{
	// the 2 first blocks of code here exist to speed up the function when very large numbers of days need adding

	if (m == Month::feb && d == 29) {													// special case if start on Feb 29th, since the day needs adjusting
		n -= 1;
		incr_day();
	}

	while (n >= 366) {																	// increment years until there aren't enough days left to form one
		if ((int(m) <= 2 && is_leapyear(y)) || (int(m) > 2 && is_leapyear(y + 1))) {	// if there is a leapday between now and the same day next year
			n -= 366;
			incr_year();
		}
		else {
			n -= 365;
			incr_year();
		}
	}

	for (int i = 0; i < n; ++i) incr_day();												// add remaining days one at a time
}

void Date::add_month(int n)   // Increase date by n months
{
	for (int i = 0; i < n; ++i) incr_month();
}

void Date::add_year(int n)   // Increase date by n years
{
	for (int i = 0; i < n; ++i) incr_year();
}

ostream& operator<<(ostream& os, const Date& d)	// Operator for outputting a date
{
	return os << '(' << d.year()
		<< ',' << int(d.month())
		<< ',' << d.day() << ')';
}

int main()
try {
	Date today{ 1978, Month::jun, 25 };			// a Date variable (a named object)

	Date tomorrow{ today };						// start off with today's date
	tomorrow.add_day(1);						// increase by 1 to get to tomorrow

	cout << today << endl << tomorrow << endl;
}
catch (InvalidDate) {
	cerr << "error: invalid date" << endl;
	return 1;
}