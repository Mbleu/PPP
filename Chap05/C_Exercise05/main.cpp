#include "..\..\std_lib_facilities.h"					// converts between Celsius and Kelvin

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

// precondition: input value k must not be less than 0 since that would be an impossible temperature below absolute zero
// postcondition: return value c must not be less than -273.15 since that would be an impossible temperature below absolute zero
double ktoc(double k)
{
	if (k < 0)
		error("error: Input temperature below abs zero.");

	double c = k - 273.15;

	if (c < -273.15)
		error("error: Return temperature below abs zero.");
	return c;
}

int main()
try {
	cout << "Please enter a temperature followed by 'c' for Celsius or 'k' for Kelvin. The program will then convert to the other.\n";
	double val = 0;										// declare input variable
	char unit = ' ';

	if (!(cin >> val))									// retrieve temperature value to input variable
		error("error: No temperature value input.");

	if (!(cin >> unit))									// retrieve temperature unit input variable
		error("error: No temperature unit input.");

	switch (unit) {
	case 'c':
		cout << ctok(val) << "k\n";								// convert and print out temperature
		break;
	case 'k':
		cout << ktoc(val) << "c\n";								// convert and print out temperature
		break;
	default:
		error("error: Unrecognised temperature unit.");
		break;
	}
}
catch (exception& e) {
	cerr << e.what();
}