#pragma once
#include "day.h"

const int not_a_month = -1;

struct Month {	// A month of temperature readings
	int month{ not_a_month };	// [0:11] January is 0
	std::vector<Day> day{ 32 };	// [1:31] one vector of readings per day
};

// Month Helper Functions:
int month_to_int(std::string s);	// is s the name of a month? If so return its index [0:11] otherwise –1
std::istream& operator>>(std::istream& is, Month& m);	// read a month from is into m, format: { month feb . . . }
void end_of_loop(std::istream& ist, char term, const std::string& message);	// check for failed read indicating the end of a read loop, if found check for terminating
																			// character. throw error message if there's a failed read but no terminating character
std::string int_to_month(int i);	// months [0:11]
void print_month(std::ofstream& ofs, const Month& m);