#include "..\..\std_lib_facilities.h"

int main()
{
	vector<string> nums{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	vector<double> inputs;
	int i_temp{ 0 };
	string s_temp{ 0 };
	char op{ ' ' };
	cout << "Enter two digits or words from 0-9/zero-nine and an operation separated by spaces (followed by 'enter'):\nAccepted operations: +, -, *, /.\n";

	for (int i{ 0 }; i < 2; ++i) {
		if (cin >> i_temp) {
			if (i_temp >= 0 && i_temp <= 9) {
				cout << i_temp << " accepted as value number " << i + 1 << ".\n";
				inputs.push_back(i_temp);
			}
			else {
				cout << "Not a digit from 0-9.\n";
				--i;
			}
		}
		else {
			cin.clear();
			cin >> s_temp;
			for (int j{ 0 }; j < nums.size(); ++j) {
				if (nums[j] == s_temp) {
					cout << j << " accepted as value number " << i + 1 << ".\n";
					inputs.push_back(j);
					break;
				}
				else if (j == nums.size() - 1) {
					cout << "Not a word from zero-nine.\n";
					--i;
				}
			}
		}
	}

	if (cin >> op) {
		switch (op) {
		case '+':
			cout << "The sum of " << inputs[0] << " and " << inputs[1] << " is " << inputs[0] + inputs[1] << ".\n";
			break;
		case '-':
			cout << "The subtraction of " << inputs[1] << " from " << inputs[0] << " is " << inputs[0] - inputs[1] << ".\n";
			break;
		case '*':
			cout << "The multiplication of " << inputs[0] << " and " << inputs[1] << " is " << inputs[0] * inputs[1] << ".\n";
			break;
		case '/':
			cout << "The division of " << inputs[0] << " by " << inputs[1] << " is " << inputs[0] / inputs[1] << ".\n";
			break;
		default:
			cout << "Invalid operation.\n";
			break;
		}
	}
	else
		cout << "Invalid operation.\n";
}