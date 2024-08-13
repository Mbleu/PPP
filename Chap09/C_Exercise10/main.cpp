/*Program for designing and testing some new helper functions for the date class.*/

#include "date.h"
#include <iostream>
using namespace std;

int main()	// Test the new helper functions
try {
	Date d1{ 2020, Month::mar, 1 };	// example date
	Date d2{ 2020, Month::mar, 1 };		// example date
	int diy{ days_into_year(d1) };
	int da{ days_apart(d1, d2) };
	Day_of_week dow{ day_of_week(d1) };
	Date nwd{ next_workday(d1) };
	int wiy{ weeks_into_year(d1) };

	cout << "Date: " << d1 << endl
		<< "Days into the year: " << diy << endl
		<< "Days between " << d1 << " and " << d2 << ": " << da << endl
		<< "Day of the week: " << dow << endl
		<< "Next workday: " << nwd << endl
		<< "Weeks into the year: " << wiy << endl;
}
catch (InvalidDate) {						// known fatal exception
	cerr << "error: invalid date" << endl;
	return 1;
}
catch (exception& e) {						// known fatal exception
	cerr << e.what() << endl;
	return 1;
}
catch (...) {								// unknown fatal exception
	return 2;
}