#pragma once
#include <iostream>

const int not_a_reading = -7777;	// less than absolute zero

struct Reading {
	int day;
	int hour;
	double temperature;
};

constexpr int implausible_min = -200;
constexpr int implausible_max = 200;

// Reading Helper Functions:
bool is_valid(const Reading& r);	// a rough test
std::istream& operator>>(std::istream& is, Reading& r);	// read in temperature reading in format ( 3 4 9.7 ), check format but not data validity