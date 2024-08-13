#include "..\..\std_lib_facilities.h"

int main()
{
	double num1{ 0 };
	double num2{ 0 };
	char op{ ' ' };
	cout << "Please enter two floating point numbers and an operation separated by spaces (followed by 'enter'):\nAccepted operations: +, -, *, /.\n";

	while (cin >> num1 >> num2 >> op) {
		switch (op) {
		case '+':
			cout << "The sum of " << num1 << " and " << num2 << " is " << num1 + num2 << ".\n";
			break;
		case '-':
			cout << "The subtraction of " << num2 << " from " << num1 << " is " << num1 - num2 << ".\n";
			break;
		case '*':
			cout << "The multiplication of " << num1 << " and " << num2 << " is " << num1 * num2 << ".\n";
			break;
		case '/':
			cout << "The division of " << num1 << " by " << num2 << " is " << num1 / num2 << ".\n";
			break;
		default:
			cout << "Invalid operation.\n";
			break;
		}
	}
}