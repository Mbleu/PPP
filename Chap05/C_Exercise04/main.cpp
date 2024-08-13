#include "..\..\std_lib_facilities.h"		// converts Celsius to Kelvin

// precondition: input value c must not be less than -273.15 since that would be an impossible temperature below absolute zero
// postcondition: return value k must not be less than 0 since that would be an impossible temperature below absolute zero
double ctok(double c)
{
	if (c < -273.15)
		error("error: Input temperature below abs zero.");

	double k = c + 273.15;

	if (k < 0)
		error("error: Return temperature below abs zero.");
	return k;
}

int main()
try {
	double c = 0;							// declare input variable
	cin >> c;								// retrieve temperature to input variable
	double k = ctok(c);						// convert temperature
	cout << k << '/n';						// print out temperature
}
catch (exception& e) {
	cerr << e.what();
}