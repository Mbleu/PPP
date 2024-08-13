/* Program for representing the date as the number of days from Jan 1st 1970 and manipulating those dates.*/

#include "date.h"
#include <iostream>
using namespace std;

int main() // Test this version of the date class and its helper functions
try {
	// Date constructors:
	Date d1{ 10000 };
	Date d2{};
	//Date d3{-1};													// invalid date

	// Member functions:
	long int d1_days{ d1.get_days() };
	d1.set_days(13001);
	d1.add_days(1000);

	// Helper functions:
	bool id1{ is_date(0) };											// valid date
	bool id2{ is_date(-100) };										// invalid date

	bool equal1{ d1 == d2 };										// unequal dates
	bool equal2{ d1 == d1 };										// equal dates

	bool notequal1{ d1 != d2 };										// unequal dates
	bool notequal2{ d1 != d1 };										// equal dates

	Day d1_dow{ day_of_week(d1) };
	Date d1_ns{ next_Sunday(d1) };
	Date d1_nwd{ next_weekday(d1) };

	cout << "Date d1: " << d1 << endl
		<< "Date d2: " << d2 << endl
		<< "d1 original number of days: " << d1_days << endl
		<< "Is 0 a valid date: " << id1 << endl
		<< "Is -100 a valid date: " << id2 << endl
		<< "d1 == d2: " << equal1 << endl
		<< "d1 == d1: " << equal2 << endl
		<< "d1 != d2: " << notequal1 << endl
		<< "d1 != d1: " << notequal2 << endl
		<< "Day of the week d1: " << d1_dow << endl
		<< "Date of the next Sunday after d1: " << d1_ns << endl
		<< "Date of the next weekday after d1: " << d1_nwd << endl;
}
catch (Date::Invalid& i) {		// known fatal errors
	cerr << i.what() << endl;
	return 1;
}
catch (...) {					// unkown fatal errors
	return 2;
}