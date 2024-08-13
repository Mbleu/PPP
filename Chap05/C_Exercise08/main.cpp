// Program that ouputs the first 'N' integers from an input list of integers
#include "..\..\std_lib_facilities.h"

bool sum_overflow(int x, int y)								// checks whether the sum of two integers will overflow
{
	if (x > 0 && y > 0)										// when both numbers are positive
		if (INT_MAX - x - y < 0)							// we subtract from max, if we delve into the negatives, we know it would have overflowed
			error("error: sum_overflow: integer overflow");
	if (x < 0 && y < 0) {									// when both numbers are negative
		if (x == INT_MIN && y == INT_MIN)					// Special check for an overflow that would be missed by the check below. This is because when the integer type is implemented
			error("error: sum_overflow: integer overflow");	// using 1's compliment, the range is 1 greater for negative values.
			
		if (INT_MIN - x - y > 0)							// we add to min, if we reach the positives, we know it would have overflowed
			error("error: sum_overflow: integer overflow");
	}

	// if one number is pos and one neg, sum overflow cannot occur

	return false;
}

int main()
try {
	cout << "Please enter the number of values 'N', you want to sum:\n";

	int num_to_sum = 0;
	if (!(cin >> num_to_sum))					// this covers any non-integer input
		error("error: invalid input for 'N'");
	if (num_to_sum < 0)							// this covers any integer input less than 0
		error("error: 'N' less than 0");

	// with all other input screened, we know we read a positive integer

	cout << "Please enter a series of integers separated by spaces. Terminate input with any non-integer character.\n";

	vector<int> vals;
	int temp_val = 0;
	while (cin >> temp_val)											// checking for non integer input and storing integers in vector
		vals.push_back(temp_val);

	if (num_to_sum > vals.size())									// throw exception if 'N' is larger than the vector size
		error("error: 'N' is greater than list of numbers");

	int sum = 0;
	cout << "The sum of the first " << num_to_sum << " numbers ( ";
	for (int i = 0; i < num_to_sum; ++i) {							// ouput list of numbers to sum and sum them
		cout << vals[i] << " ";
		sum_overflow(sum, vals[i]);									// check that the sum will not cause an overflow before attempting it
		sum += vals[i];
	}
	cout << ") is " << sum << ".\n";
}
catch (exception& e) {
	cerr << e.what();
}