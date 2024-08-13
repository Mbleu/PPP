#include "..\..\std_lib_facilities.h"

vector<string> find_modes(vector<string> strings)
{
	sort(strings);
	string curr_string{ strings[0] };	// keeps track of the current string we are looking at
	int curr_string_count{ 0 };			// keeps track of how many times the current string has appeared
	vector<string> modes;				// keeps track of the current mode candidates with the highest appearances, and ultimately the final modes
	int mode_count{ 0 };				// keeps track of the number of appearances of the current mode candidates in modes

	for (string s : strings) {
		if (curr_string != s) {
			curr_string = s;
			curr_string_count = 1;
		}
		else
			++curr_string_count;

		if (curr_string_count == mode_count)
			modes.push_back(curr_string);
		else if (curr_string_count > mode_count) {
			modes.clear();
			modes.push_back(curr_string);
			mode_count = curr_string_count;
		}
	}
	return modes;
}

int main()
{
	vector<string> strings;
	string temp_string{ 0 };
	vector<string> modes;
	
	cout << "Enter a sequence of strings separated by spaces (followed by 'enter'):\n";

	while (cin >> temp_string)
		strings.push_back(temp_string);
	
	sort(strings);
	cout << "Min: " << strings.front() << '\n';
	cout << "Max: " << strings.back() << '\n';

	modes = find_modes(strings);
	cout << "The mode(s) of the series entered is(are): ";
	for (string s : modes)
		cout << s << ' ';
}