#pragma once
#include <iostream>

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

enum class Day_of_week {
	sun = 0, mon, tue, wed, thu, fri, sat
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
class InvalidDate {};	// For throwing exceptions
bool is_leapyear(int y);	// check if a year is a leapyear or not
std::ostream& operator<<(std::ostream& os, const Date& d);	// operator for outputting a date

// New set of helper functions:
std::ostream& operator<<(std::ostream& os, Day_of_week dow);	// operator for outputting a day of the week
bool operator==(const Date& d1, const Date& d2);	// operator for comparing dates
bool operator!=(const Date& d1, const Date& d2);	// operator for comparing dates
bool operator<(const Date& d1, const Date& d2);	// operator for comparing dates
bool operator>(const Date& d1, const Date& d2);	// operator for comparing dates
bool operator<=(const Date& d1, const Date& d2);	// operator for comparing dates
bool operator>=(const Date& d1, const Date& d2);	// operator for comparing dates
int days_into_year(const Date& d1);	// returns how many days into the year a date is
int days_apart(const Date& d1, const Date& d2);	// returns the number of days between 2 dates
Day_of_week day_of_week(const Date& d);	// returns the day of the week (sun-sat) of a date
Date next_workday(Date d);	// next day that is not on a weekend
int weeks_into_year(const Date& d);	// returns the week of the year that the date is in (1-52), weeks are Sunday-Saturday