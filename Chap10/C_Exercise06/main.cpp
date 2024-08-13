/*Program for creating and manipulating roman numerals and their integer values.*/

#include "roman.h"
#include <iostream>
using namespace std;

void discard_input(istream& is)	// Discard input from buffer up to the next newline
{
	is.clear();
	while (is.get() != '\n');	// discard up to the next newline (console won't provide an eof)
}

int main()	// Test the facilities of the Roman namespace
try {
	// Output a roman number:
	Roman::Number rnumber{ 3879 };
	cout << rnumber << endl
		<< "Int: " << rnumber.as_int() << endl;

	// Input and then output a roman number:
	cin.exceptions(cin.exceptions() | ios_base::badbit);	// throw exception if cin goes bad
	cout << "Please enter a roman number as either an integer or numeral to have it converted:" << endl;
	while (1) {												// loop forever
		cout << '>';
		if (!(cin >> rnumber)) {
			cerr << "Invalid number." << endl;
			discard_input(cin);
			continue;
		}
		cout << rnumber << endl
			<< "Int: " << rnumber.as_int() << endl;
	}
}
catch (exception& e) {	// Print error and quit
	cerr << e.what() << endl;
	return 1;
}