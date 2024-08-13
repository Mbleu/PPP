#pragma once
#include <vector>
#include <fstream>
#include "reading.h"

struct Day {
	std::vector<double> hour{ std::vector<double>(24,not_a_reading) };
};

// Day Helper Functions:
void print_day(std::ofstream& ofs, const Day& d);