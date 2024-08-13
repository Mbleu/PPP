#include "..\..\std_lib_facilities.h"		// converts Celsius to Kelvin

double ctok(double c)
{
	double k = c + 273.15;
	return k;
}

int main()
try {
	double c = 0;							// declare input variable
	cin >> c;								// retrieve temperature to input variable
	if (c < -273.15)
		error("error: Temperature below abs zero.");
	double k = ctok(c);						// convert temperature
	cout << k << '/n';						// print out temperature
}
catch (exception& e) {
	cerr << e.what();
}