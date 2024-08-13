// Program for calculating the number of permutations or combinations of two given numbers

#include "..\..\std_lib_facilities.h"

int factorial(int num)	// takes a number and returns its factorial
{
	if (num < 0) error("error: factorial: negative value received");				// pre: number must be positive
	if (num == 0) return 1;															// 0! == 1 by convention

	constexpr int imin = std::numeric_limits<int>::min();							// min and max int values
	constexpr int imax = std::numeric_limits<int>::max();
	long long big_num{ num };														// larger variable to detect overflows
	for (int i = big_num - 1; i > 0; --i) {
		big_num *= i;
		if (big_num < imin || big_num > imax) error("error: factorial: overflow");	// overflow detected
	}

	if (big_num <= 0) error("error: factorial: negative or zero value calculated");	// post: number must be postive and non-zero
	return big_num;
}

int permutation(int a, int b)	// takes two numbers and returns the number of permutations
{
	if (a <= 0 || b <= 0) error("error: permutation: negative or zero value received");	// pre: received numbers must be positive and non-zero

	int perms{factorial(a) / factorial(a - b)};											// post: calculated number of permutations must be non-narrowed integer
	if (perms <= 0) error("error: permutation: negative or zero value calculated");		// post: calculated number of permutations must be postive and non-zero
	return perms;
}

int combination(int a, int b)
{
	if (a <= 0 || b <= 0) error("error: permutation: negative or zero value received");	// pre: received numbers must be positive and non-zero

	int combs{ permutation(a, b) / factorial(b) };										// post: calculated number of combinations must be non-narrowed integer
	if (combs <= 0) error("error: permutation: negative or zero value calculated");		// post: calculated number of combinations must be postive and non-zero
	return combs;
}

int main()
try {
	cout << "Welcome to the permutation / combination calculator.\n"
		<< "First, please enter two positive integer numbers separated by spaces.\n";

	int num1{0};
	int num2{0};

	if (!(cin >> num1) || num1 <= 0) error("error: bad number input");						// read in two positive integers
	if (!(cin >> num2) || num2 <= 0) error("error: bad number input");

	cout << "Would you like to calculate the number of permutations or combinations?\n"
		<< "Please enter 'p' or 'c'.\n";

	char c{' '};
	while(c != 'p' && c != 'c')																// loop until valid option chosen
	{
		if (!(cin >> c)) error("error: bad char input");									// read in whether user wants perm or comb
		switch (c) {
		case 'p':
			cout << "Number of permutations: " << permutation(num1, num2) << '\n';			// return permutation
			break;
		case 'c':
			cout << "Number of combinations: " << combination(num1, num2) << '\n';			// return combination
			break;
		default:
			cout << "Invalid input.\n";
			break;
		}
	}

	return 0;
}
catch (exception& e) {
	cerr << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "error: unkown exception\n";
	return 2;
}