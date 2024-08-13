#include "..\..\std_lib_facilities.h"

int main()
{
	cout << "Please enter the number of miles you want converted into kilometeres (followed by 'enter'):\n";
	double miles = 0;
	double km = 0;
	cin >> miles;
	km = miles * 1.609;
	cout << miles << " miles is equal to " << km << " kilometers.\n";
}