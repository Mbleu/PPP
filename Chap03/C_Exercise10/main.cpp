#include "..\..\std_lib_facilities.h"

int main()
{
	cout << "Please enter an operation followed by two numbers, each separated by a 'space' (followed by 'enter'):\n" << "Example: + 2.3 7\n";
	string operation = " ";
	double val1 = 0;
	double val2 = 0;
	cin >> operation >> val1 >> val2;

	if (operation == "+") {
		cout << val1 << ' ' << operation << ' ' << val2 << " = " << val1 + val2;
	}
	else if (operation == "-") {
		cout << val1 << ' ' << operation << ' ' << val2 << " = " << val1 - val2;
	}
	else if (operation == "*") {
		cout << val1 << ' ' << operation << ' ' << val2 << " = " << val1 * val2;
	}
	else if (operation == "/") {
		cout << val1 << ' ' << operation << ' ' << val2 << " = " << val1 / val2;
	}
}