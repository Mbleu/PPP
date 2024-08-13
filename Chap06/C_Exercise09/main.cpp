#include "..\..\std_lib_facilities.h"

int main()
try {
	cout << "Enter a number, up to 4 digits long, to have it split into its orders of magnitude. End each number with a ';'.\n";

	int number{ 0 };

	for (int i = 4; i > 0; --i) {								// read in up to 4 digits
		char c{ ' ' };
		int digit{ 0 };
		if (!(cin >> c)) error("error: bad input");
		if (c == ';') break;
		digit = c - '0';												// converts a char digit to an int digit
		if (digit < 0 || digit > 9) error("error: non digit");
		number *= 10;													// bump up the number to accomodate the new digit
		number += digit;												// add digit to 1st order of magnitude
	}
	if (number == 0) error("error: number has value 0");

	bool firstdig{ true };												// keeps track of the first non zero digit for grammatical purposes
	cout << number << " is ";									// ouput number broken down into component magnitudes
	if (number >= 1000) {
		if (!firstdig) cout << " and ";
		firstdig = false;
		if (number / 1000 == 1)
			cout << "1 thousand";
		else cout << number / 1000 << " thousands";
	}
	number %= 1000;
	if (number >= 100) {
		if (!firstdig) cout << " and ";
		firstdig = false;
		if (number / 100 == 1)
			cout << "1 hundred";
		else cout << number / 100 << " hundreds";
	}
	number %= 100;
	if (number >= 10) {
		if (!firstdig) cout << " and ";
		firstdig = false;
		if (number / 10 == 1)
			cout << "1 ten";
		else cout << number / 10 << " tens";
	}
	number %= 10;
	if (number >= 1) {
		if (!firstdig) cout << " and ";
		firstdig = false;
		if (number == 1)
			cout << "1 one";
		else cout << number << " ones";
	}
}
catch (exception& e) {
	cerr << e.what() << '\n';
}
catch (...) {
	cerr << "error: unknown exception\n";
}