#include "..\..\std_lib_facilities.h"

int main()
{
	cout << "Please enter your first name and age\n";
	string first_name;	// string variable
	double age;			// floating point variable
	cin >> first_name;	// read a string
	cin >> age;			// read an integer
	cout << "Hello, " << first_name << " (age " << age * 12 << " months)\n";
}