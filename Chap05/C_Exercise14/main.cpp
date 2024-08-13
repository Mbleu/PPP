/*Program for reading in (day-of-the-week, value) pairs, storing them and then outputting them. */

#include "..\..\std_lib_facilities.h"

bool sum_overf(int x, int y)														// checks whether the sum of two integers will overflow
{
	if (x > 0 && y > 0)																// when both pos
		if (INT_MAX - x < y)
			error("error: sum_overflow: integer overflow");

	if (x < 0 && y < 0)																// when both neg
	{
		if (x == INT_MIN && y == INT_MIN)											// special case not caught below due to 1's compliment causing neg vals to have a larger range by 1
			error("error: sum_overflow: integer overflow");

		if (INT_MIN - x > y)														// doesn't catch the special case above
			error("error: sum_overflow: integer overflow");
	}
																					// when one pos and one neg, overflow is impossible
	return false;
}

struct Day {
	vector<string> aliases;															// acceptable inputs to refer to the day
	vector<int> values;

	Day(vector<string> aliases)														// constructor that demands a list of aliases upon instantiation
		: aliases(aliases) {}

	int sum()																		// returns the sum of values
	{
		int sum = 0;
		for (int x : values) {
			sum_overf(sum, x);
			sum += x;
		}
			
		return sum;
	}
};

int main()
try {
	vector<Day> days;
	days.push_back(Day({ "monday", "mon" }));										// instantiating the days of the week
	days.push_back(Day({ "tuesday", "tu", "tue", "tues" }));
	days.push_back(Day({ "wednesday", "wed" }));
	days.push_back(Day({ "thursday", "thu", "thur", "thurs" }));
	days.push_back(Day({ "friday", "fri" }));
	days.push_back(Day({ "saturday", "sat" }));
	days.push_back(Day({ "sunday", "sun" }));

	cout << "Please enter \"day-of-the-week, value\" pairs with each element and pair separated by a space.\n"
		<< "e.g. Tuesday 23 Friday 56 Tuesday -3 Thursday 99\n"
		<< "Invalid days or numbers won't be counted. Terminate input by entering 'x' in place of a day.\n\n";

	bool end_input = false;
	int rej_vals = 0;																// number of values rejected due to invalid day

	while (!end_input)
	{
		string temp_day = "";

		if (cin >> temp_day)
		{
			if (temp_day != "x")													// check if the user has terminated here
			{
				for (char & c : temp_day)											// make the input string lower case
					c = tolower(c);

				int temp_val = 0;

				if (cin >> temp_val) {

					bool alias_found = false;										// flag for checking whether a match has been found for the input day

					for (Day & day : days)											// iterate through the days
						for (string & alias : day.aliases)							// iterate through the aliases for each day
							if (temp_day == alias) {
								day.values.push_back(temp_val);						// match found for input day, so add input value to its vector
								alias_found = true;
							}

					if (!alias_found)												// no match found for input day, so increment number of rejected values
						++rej_vals;
				}
				else
					error("error: Invalid input for value.");
			}
			else
				end_input = true;
		}
		else
			error("error: Invalid input for day.");
	}

	for (Day day : days)															// output sum of values for each day
		cout << "Sum for " << day.aliases[0] << ": " << day.sum() << '\n';

	cout << "Number of values rejected due to invalid day: " << rej_vals << '\n';
}
catch (exception& e) {
	cerr << e.what();
}