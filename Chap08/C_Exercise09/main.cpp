/*Program that asks for prices and weights, then prints the list of price-weight pairs and computes the sum of factor pairs.*/

#include <vector>
#include <iostream>
using namespace std;

void print_pairs(const vector<double>& vs, const vector<double>& vd)	// Prints out vector pairs
{
	for (int i = 0; i < vs.size(); ++i) {
		cout << "( " << vs[i] << ", " << vd[i] << " )" << endl;
	}
}

double sum_factor_pairs(const vector<double>& v1, const vector<double>& v2)	// Multiplies the values of 2 same sized vectors in pairs and sums
{
	if (v1.size() != v2.size()) throw exception("error: sum_factor_pairs(): received vectors of unequal size");	// pre: vectors must be of equal size

	double sum{ 0 };
	for (int i = 0; i < v1.size(); ++i) {
		sum += v1[i] * v2[i];
	}
	return sum;
}

void clear_is()	// Discards input up to and including the next newline.
{
	while (cin.get() != '\n');
}

int main()
try {
	cout << "Please enter a list of prices. Press 'enter' between each one." << endl
		<< "To stop entering prices, type ';' on its own." << endl;
	vector<double> prices;
	vector<double> weights;

	while (1) try {																											// read in prices
		cout << "> ";
		double d_input{0};

		if (!(cin >> d_input) || cin.peek() != '\n') {																		// invalid price input
			cin.clear();
			string s_input = "";
			cin >> s_input;
			if (s_input == ";") break;																						// user ends input
			throw exception("error: main: invalid input price");
		}
		if (d_input <= 0) throw exception("error: main: non-positive input price");

		prices.push_back(d_input);																							// valid price input
	}
	catch (exception& e) {																									// handle bad input to allow for re-entry
		cerr << e.what() << endl;
		cin.clear();
		clear_is();
	}

	cout << endl << "Enter a weight for the following prices:" << endl;
	while (weights.size() != prices.size()) try {																			// read in weights
		cout << prices[weights.size()] << " > ";																			// prompt user with price to input weight for
		double d_input{ 0 };
		if (!(cin >> d_input) || d_input <= 0 || cin.peek() != '\n') throw exception("error: main: invalid input weight");
		weights.push_back(d_input);
	}
	catch (exception& e) {																									// handle bad input to allow for re-entry
		cerr << e.what() << endl;
		cin.clear();
		clear_is();
	}

	cout << endl << "List of price-weight pairs:" << endl;
	print_pairs(prices, weights);

	cout << endl << "Sum of factor pairs:" << endl;
	cout << sum_factor_pairs(prices, weights) << endl;
}
catch (...) {
	return 1;
}