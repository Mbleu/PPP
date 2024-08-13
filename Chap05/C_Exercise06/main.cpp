#include "..\..\std_lib_facilities.h"							// converts between Celsius and Fahrenheit

// precondition: input value c must not be less than -273.15 since that would be an impossible temperature below absolute zero
// postcondition: return value f must not be less than -459.67 since that would be an impossible temperature below absolute zero
double ctof(double c)
{
	if (c < -273.15)
		error("error: Input temperature below abs zero.");

	double f = 9.0/5.0*c+32;									// formula to convert Celsius to Fahrenheit

	if (f < -459.67)
		error("error: Return temperature below abs zero.");
	return f;
}

// precondition: input value f must not be less than -459.67 since that would be an impossible temperature below absolute zero
// postcondition: return value c must not be less than -273.15 since that would be an impossible temperature below absolute zero
double ftoc(double f)
{
	if (f < -459.67)
		error("error: Input temperature below abs zero.");

	double c = (5.0*f-160.0)/9.0;								// formula to convert Celsius to Fahrenheit

	if (c < -273.15)
		error("error: Return temperature below abs zero.");
	return c;
}

int main()
try {
	cout << "Please enter a temperature followed by 'c' for Celsius or 'f' for Fahrenheit. The program will then convert to the other.\n";
	double val = 0;												// declare input variable
	char unit = ' ';

	if (!(cin >> val))											// retrieve temperature value to input variable
		error("error: No temperature value input.");

	if (!(cin >> unit))											// retrieve temperature unit input variable
		error("error: No temperature unit input.");

	switch (unit) {
	case 'c':
		cout << ctof(val) << "f\n";								// convert and print out temperature
		break;
	case 'f':
		cout << ftoc(val) << "c\n";								// convert and print out temperature
		break;
	default:
		error("error: Unrecognised temperature unit.");
		break;
	}
}
catch (exception& e) {
	cerr << e.what();
}