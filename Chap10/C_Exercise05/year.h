#pragma once
#include <vector>
#include <iostream>
#include "month.h"

struct Year {	// A year of temperature readings, organized by month
	int year;						// positive == A.D.
	std::vector<Month> month{ 12 };	// [0:11] January is 0
};

std::istream& operator>>(std::istream& is, Year& y);	// read a year from is into y, format: { year 1972 . . . }
void print_year(std::ofstream& ofs, const Year& y);