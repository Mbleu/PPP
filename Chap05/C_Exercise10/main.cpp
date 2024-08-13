// Program that ouputs the first 'N' integers from an input list of integers
#include "..\..\std_lib_facilities.h"

int main()
try {
	cout << "Please enter the number of values 'N', you want to sum:\n";

	int num_to_sum = 0;
	if (!(cin >> num_to_sum))					// this covers any non-integer input
		error("error: invalid input for 'N'");
	if (num_to_sum < 0)							// this covers any integer input less than 0
		error("error: 'N' less than 0");

	// with all other input screened, we know we read a positive integer

	cout << "Please enter a series of numbers separated by spaces. Terminate input with any non-digit character.\n";

	vector<double> vals;
	double temp_val = 0;
	while (cin >> temp_val)											// checking for non numerical input and storing numbers in vector
		vals.push_back(temp_val);

	if (num_to_sum > vals.size())									// throw exception if 'N' is larger than the vector size
		error("error: 'N' is greater than list of numbers");

	
	int sum = 0;
	cout << "The sum of the first " << num_to_sum << " numbers ( ";
	for (int i = 0; i < num_to_sum; ++i) {							// ouput list of numbers to sum and sum them
		cout << vals[i] << " ";
		sum += vals[i];
	}
	cout << ") is " << sum << ".\n";

	cout << "Differences between adjacent values of the sum: ";
	vector<double> difs;
	for (int i = 1; i < num_to_sum; ++i) {							// calculate differences between adjacent values and ouput them
		difs.push_back(vals[i] - vals[i - 1]);
		cout << difs[i - 1] << ' ';
	}
	cout << ".\n";
}
catch (exception& e) {
	cerr << e.what();
}