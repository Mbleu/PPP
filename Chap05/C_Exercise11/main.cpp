#include "..\..\std_lib_facilities.h"

int main()
try {
	cout << "Please enter how many values of the Fibonacci sequence you would like.\n";
	int num_of_vals = 0;
	if (!(cin >> num_of_vals) || num_of_vals < 0)	// only accept positive integers
		error("error: invald number of values");

	int previous = 0;								// the previous value in the sequence
	int current = 1;								// the current value in the sequence, initially set to the first value
	int temp = 0;									// a temp variable for storing data whilst changing values in the loop
	for (int i = 0; i < num_of_vals; ++i) {			// ouputs the current value, calculates the next value and moves along the variables
		cout << current << ' ';
		temp = current;
		current += previous;
		previous = temp;
		if (current < 0)
			error("error: int overflow");
	}
}
catch (exception& e) {
	cerr << e.what();
}