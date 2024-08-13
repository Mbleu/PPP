#pragma once
#include <iostream>

enum class Day {
	sun, mon, tue, wed, thu, fri, sat
};

class Date {
public:
	class Invalid {
	public:
		Invalid(const std::string& s) : s(s) {}
		const std::string& what() const { return s; }

	private:
		std::string s;
	};

	Date(const long int days) { set_days(days); }	// initialise date
	Date() { set_days(0); }							// initialise to default date, Jan 1st 1970
	long int get_days() const { return days; }
	void set_days(long int days);					// check for valid date and set it
	void add_days(const long int days);				// add a number of days to the date

private:
	long int days;									// number of days since Jan 1st 1970, known as day 0
};

// Helper functions:
bool is_date(const long int days);	// check if date is valid
bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);
std::ostream& operator<<(std::ostream& os, const Date& d);
std::istream& operator>>(std::istream& is, Date& d);
std::ostream& operator<<(std::ostream& os, const Day d);
Day day_of_week(const Date& d);	// day of week of d
Date next_Sunday(const Date& d);	// next Sunday after d
Date next_weekday(const Date& d);	// next weekday after d