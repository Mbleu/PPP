#include "..\..\std_lib_facilities.h"

int main()
{
	cout << "Please type the number you want converted into a digit (followed by 'enter'):\n";
	string num = " ";
	int dig = 0;
	bool numRecognised = true;

	cin >> num;
	if (num == "zero" || num == "Zero") {
		dig = 0;
	}
	else if (num == "one" || num == "One") {
		dig = 1;
	}
	else if (num == "two" || num == "Two") {
		dig = 2;
	}
	else if (num == "three" || num == "Three") {
		dig = 3;
	}
	else if (num == "four" || num == "Four") {
		dig = 4;
	}
	else {
		cout << num << " is not a number I know.";
		numRecognised = false;
	}

	if (numRecognised) {
		cout << num << " written as a digit is " << dig << '.';
	}
}