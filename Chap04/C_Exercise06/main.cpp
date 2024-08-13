#include "..\..\std_lib_facilities.h"

int main()
{
	vector<string> nums{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	int i_input{ 0 };
	string s_input{ "" };
	cout << "Enter a digit from 0-9 to convert it to a word or vice versa (followed by 'enter'):\n";

	while (1) {
		if (cin >> i_input) {
			if (i_input >= 0 && i_input <= 9)
				cout << nums[i_input] << '\n';
			else
				cout << "Not a digit from 0-9.\n";
		}
		else {
			cin.clear();
			cin >> s_input;
			for (int i{ 0 }; i < nums.size(); ++i) {
				if (nums[i] == s_input) {
					cout << i << '\n';
					break;
				}
				else if (i == nums.size() - 1)
					cout << "Not a word from zero-nine.\n";
			}
		}
	}
}