#include "..\..\std_lib_facilities.h"

int main()
{
	cout << "Please enter an integer value to determine if it is odd or even (followed by 'enter'):\n";
	int val = 0;
	cin >> val;

	if (val % 2 == 0) {
		cout << "The number " << val << " is even.";
	}
	else {
		cout << "The number " << val << " is odd.";
	}
}