#include "..\..\std_lib_facilities.h"

double convert_to_m(double val, string unit) // Converts lengths of different units into m
{
	constexpr double cm_to_m = 100;
	constexpr double cm_to_in = 2.54;
	constexpr double in_to_ft = 12;

	if (unit == "cm")
		return val / cm_to_m;
	else if (unit == "m")
		return val;
	else if (unit == "in")
		return val * cm_to_in / cm_to_m;
	else if (unit == "ft")
		return val * in_to_ft * cm_to_in / cm_to_m;
	else
		error("Unrecognised unit.");
}

int main()
{
	vector<double> vals;
	double curr_val = 0;
	string curr_val_unit = "";

	cout << "Please enter a length, for example 12.6cm (followed by 'enter').\nThe accepted units are: cm, m, in and ft.\n";

	// For the first length entered
	if (cin >> curr_val >> curr_val_unit) {
		curr_val = convert_to_m(curr_val, curr_val_unit);
		curr_val_unit = "m";
		vals.push_back(curr_val);
		sort(vals);
		cout << "Length entered: " << curr_val << curr_val_unit << '\n';
	}
	else
		return 0;

	// For all subsequent lengths entered
	while (cin >> curr_val >> curr_val_unit) {
		curr_val = convert_to_m(curr_val, curr_val_unit);
		curr_val_unit = "m";
		vals.push_back(curr_val);
		sort(vals);
		cout << "Length entered was: " << curr_val << curr_val_unit;
		if (curr_val <= vals.front())
			cout << ", the smallest length so far";
		if (curr_val >= vals.back())
			cout << ", the largest length so far";
		cout << '\n';
	}

	// Prints a list of lengths entered in order of size as well as a summary
	double sum = 0;
	cout << "List of lengths:\n";
	for (double d : vals) {
		cout << d << "m\n";
		sum += d;
	}
	cout << "The smallest length was: " << vals.front() << curr_val_unit << "\nThe largest length was: " << vals.back() << curr_val_unit 
		<< "\nThe number of lengths entered was: " << vals.size() << "\nThe sum of all lengths was: " << sum << curr_val_unit << '\n';
}