/*Program that asks for 5 names and ages, then prints the list of name-value pairs before and after sorting.*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void print_pairs(const vector<string>& vs, const vector<int>& vd)	// prints out name value pairs
{
	for (int i = 0; i < vs.size(); ++i) {
		cout << "( " << vs[i] << ", " << vd[i] << " )" << endl;
	}
}

void clear_is()	// Discards input up to and including the next newline.
{
	while (cin.get() != '\n');
}

int main()
try {
	cout << "Please enter 5 names:" << endl;
	vector<string> names;
	vector<int> ages;

	while (names.size() < 5) try {																						// read in names
		cout << "> ";
		string s_input;
		if (!(cin >> s_input) || cin.peek() != '\n') throw exception("error: main: invalid input name");
		for (string name : names)
			if (s_input == name) throw exception("error: main: invalid input, name already exists");
		names.push_back(s_input);
	}
	catch (exception& e) {																								// handle bad input to allow for re-entry
		cerr << e.what() << endl;
		cin.clear();
		clear_is();
	}

	cout << endl << "Enter an age for:" << endl;
	while (ages.size() != names.size()) try {																			// read in ages
		cout << names[ages.size()] << " > ";																			// prompt user with name to input age for
		int i_input{0};
		if (!(cin >> i_input) || i_input < 0 || cin.peek() != '\n') throw exception("error: main: invalid input age");
		ages.push_back(i_input);
	}
	catch (exception& e) {																								// handle bad input to allow for re-entry
		cerr << e.what() << endl;
		cin.clear();
		clear_is();
	}

	cout << endl << "List of name-age pairs:" << endl;
	print_pairs(names, ages);

	vector<string> names_sorted{ names };																				// sort names
	sort(names_sorted.begin(), names_sorted.end());

	vector<int> ages_sorted{ ages };																					// sort ages
	for (int i = 0; i < names.size(); ++i)
		for (int j = 0; j < names_sorted.size(); ++j)
			if (names[i] == names_sorted[j])
				ages_sorted[j] = ages[i];

	cout << endl << "Sorted list of name-age pairs:" << endl;
	print_pairs(names_sorted, ages_sorted);
}
catch (...) {
	return 1;
}