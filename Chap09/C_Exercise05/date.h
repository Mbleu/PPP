#pragma once
#include <iostream>

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
class InvalidDate{};	// For throwing exceptions
bool is_leapyear(int y);	// check if a year is a leapyear or not
std::ostream& operator<<(std::ostream& os, const Date& d);	// operator for outputting a date