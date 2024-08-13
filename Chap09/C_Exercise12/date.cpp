#include "date.h"

void Date::set_days(long int days)	// Check for valid date and set it
{
	if (!is_date(days)) throw Invalid("error: Date::Date(const long int): received invalid date");	// pre: must be a valid date
	this->days = days;
}

void Date::add_days(const long int days)	// Add a number of days to the date
{
	is_date(this->days + days);	// pre: new date must be valid after adding days
	this->days += days;
}

// Helper functions:
bool is_date(const long int days)	// Check if date is valid
{
	if (days < 0) return false;
	return true;
}

bool operator==(const Date& a, const Date& b)
{
	if (a.get_days() == b.get_days()) return true;
	return false;
}

bool operator!=(const Date& a, const Date& b)
{
	return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
	return os << d.get_days();
}

std::istream& operator>>(std::istream& is, Date& d)
{
	long int dd{ 0 };
	if (is >> dd) d.set_days(dd);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Day d)
{
	switch (d) {
	case Day::sun:
		return os << "Sunday";
	case Day::mon:
		return os << "Monday";
	case Day::tue:
		return os << "Tuesday";
	case Day::wed:
		return os << "Wednesday";
	case Day::thu:
		return os << "Thursday";
	case Day::fri:
		return os << "Friday";
	case Day::sat:
		return os << "Saturday";
	default:
		throw Date::Invalid("error: operator<<(std::ostream& os, const Day): received invalid day of the week");
	}
}

Day day_of_week(const Date& d)	// Day of week of d
{
	if (d.get_days() < 0) throw Date::Invalid("error: day_of_week(const Date&): received negative date");	// pre
	int days_to_shift{ d.get_days() % 7 };																	// remove whole weeks since and get remainder
	Day day{ Day::thu };																					// start from day of the week of Jan 1st 1970, day 0
	day = Day((int(day) + days_to_shift) % 7);																// % 7 to remove potential whole week
	return day;
}

Date next_Sunday(const Date& d)	// Next Sunday after d
{
	Day day{ day_of_week(d) };
	int days_to_shift{ 7 - int(day) };
	return Date(d.get_days() + days_to_shift);
}

Date next_weekday(const Date& d)	// Next weekday after d
{
	Day day{ day_of_week(d) };
	if (day == Day::fri) return Date(d.get_days() + 3);
	if (day == Day::sat) return Date(d.get_days() + 2);
	return Date(d.get_days() + 1);
}