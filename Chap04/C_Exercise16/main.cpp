#include "..\..\std_lib_facilities.h"

vector<int> find_modes(vector<int> vals)
{
	sort(vals);
	int curr_val{ vals[0] };	// keeps track of the current value we are looking at
	int curr_val_count{ 0 };	// keeps track of how many times the current value has appeared
	vector<int> modes;			// keeps track of the current mode candidates with the highest appearances, and ultimately the final modes
	int mode_count{ 0 };		// keeps track of the number of appearances of the current mode candidates in modes

	for (int v : vals) {
		if (curr_val != v) {
			curr_val = v;
			curr_val_count = 1;
		}
		else
			++curr_val_count;

		if (curr_val_count == mode_count)
			modes.push_back(curr_val);
		else if (curr_val_count > mode_count) {
			modes.clear();
			modes.push_back(curr_val);
			mode_count = curr_val_count;
		}
	}
	return modes;
}

int main()
{
	vector<int> vals;
	int temp_val{ 0 };
	vector<int> modes;
	cout << "Enter a series of positive integers separated by spaces (followed by 'enter'):\n";

	while (cin >> temp_val)
		vals.push_back(temp_val);

	modes = find_modes(vals);
	cout << "The mode(s) of the series entered is(are): ";
	for (int v : modes)
		cout << v << ' ';
}