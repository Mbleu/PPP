#include "date.h"
#include <iostream>
#include <cmath>
using namespace std;

// Helper functions:
bool is_leapyear(int y)	// Check if a year is a leapyear or not
{
	if (y % 4 != 0) return false;
	if (y % 100 == 0 && y % 400 != 0) return false;
	return true;
}

ostream& operator<<(ostream& os, const Date& d)	// Operator for outputting a date
{
	return os << '(' << d.year()
		<< ',' << int(d.month())
		<< ',' << d.day() << ')';
}

ostream& operator<<(ostream& os, Day_of_week dow)	// operator for outputting a day of the week
{
	switch (dow) {
	case Day_of_week::sun:
		return os << "Sunday";
	case Day_of_week::mon:
		return os << "Monday";
	case Day_of_week::tue:
		return os << "Tuesday";
	case Day_of_week::wed:
		return os << "Wednesday";
	case Day_of_week::thu:
		return os << "Thursday";
	case Day_of_week::fri:
		return os << "Friday";
	case Day_of_week::sat:
		return os << "Saturday";
	default:
		throw exception("error: operator<<(std::ostream& os, Day_of_week): received invalid day of the week");
	}
}

bool operator==(const Date& d1, const Date& d2)	// Operator for comparing dates
{
	if (d1.year() == d2.year() && int(d1.month()) == int(d2.month()) && d1.day() == d2.day())
		return true;
	return false;
}

bool operator!=(const Date& d1, const Date& d2) { return !(d1 == d2); }	// Operator for comparing dates

bool operator<=(const Date& d1, const Date& d2)	// Operator for comparing dates
{
	if (d1.year() > d2.year()) return false;
	if (d1.year() == d2.year() && int(d1.month()) > int(d2.month())) return false;
	if (d1.year() == d2.year() && int(d1.month()) == int(d2.month()) && d1.day() > d2.day()) return false;
	return true;
}

bool operator>=(const Date& d1, const Date& d2)	// Operator for comparing dates
{
	if (d1.year() < d2.year()) return false;
	if (d1.year() == d2.year() && int(d1.month()) < int(d2.month())) return false;
	if (d1.year() == d2.year() && int(d1.month()) == int(d2.month()) && d1.day() < d2.day()) return false;
	return true;
}

bool operator<(const Date& d1, const Date& d2) { return !(d1 >= d2); }	// Operator for comparing dates

bool operator>(const Date& d1, const Date& d2) { return !(d1 <= d2); }	// Operator for comparing dates

int days_into_year(const Date& d1)	// Returns how many days into the year a date is
{
	int n{ 0 };																			// days into the year

	n += d1.day();																		// add the days into the current month

	switch (d1.month()) {																// add days from previous months (starting with the previous month)
	case Month::dec: n += 30;
	case Month::nov: n += 31;
	case Month::oct: n += 30;
	case Month::sep: n += 31;
	case Month::aug: n += 31;
	case Month::jul: n += 30;
	case Month::jun: n += 31;
	case Month::may: n += 30;
	case Month::apr: n += 31;
	case Month::mar: 
		if (is_leapyear(d1.year())) n += 29;
		else n += 28;
	case Month::feb: n += 31;
	case Month::jan: return n;
	default:
		throw exception("error: days_into_year(const Date&): received invalid month");
	}
}

int days_apart(const Date& d1, const Date& d2)	// Returns the number of days between 2 dates
{
	int apart{ 0 };											// days apart

	if (d1 < d2) {
		for (int i = 0; i < d2.year() - d1.year(); ++i) {	// add days of years apart
			if (is_leapyear(d1.year() + i)) apart += 366;
			else apart += 365;
		}
	}
	else {
		for (int i = 0; i < d1.year() - d2.year(); ++i) {	// add days of years apart
			if (is_leapyear(d1.year() - i)) apart -= 366;
			else apart -= 365;
		}
	}

	apart += days_into_year(d2) - days_into_year(d1);		// add/subtract days of partial year at either end

	return apart;
}

Day_of_week day_of_week(const Date& d)	// Returns the day of the week (sun-sat) of a date
{
	Date d_sun{ 2006, Month::jan, 1 };						// date of a known sunday

	int apart{ days_apart(d_sun, d) };

	int days_to_shift{ apart % 7 };							// divide by 7 to remove the weeks, remainder is the days to shift

	Day_of_week dow{ Day_of_week::sun };

	if (days_to_shift < 0) days_to_shift += 7;

	dow = Day_of_week(int(dow) + days_to_shift);

	return dow;
}

Date next_workday(Date d)	// Next day that is not on a weekend
{
	switch (day_of_week(d)) {
	case Day_of_week::fri:
		d.incr_day();
	case Day_of_week::sat:
		d.incr_day();
	default: 
		d.incr_day();
		return d;
	}
}

int weeks_into_year(const Date& d)	// Returns the week of the year that the date is in (1-52), weeks are Sunday-Saturday
{
	Day_of_week dow_01jan{ day_of_week(Date(d.year(), Month::jan, 1))};		// day of the week of the 1st of Jan
	int days_in_first_week{7 - int(dow_01jan)};
	
	return 1 + ceil((days_into_year(d) - days_in_first_week) / double(7));	// always round up, the 1 counts the first week
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