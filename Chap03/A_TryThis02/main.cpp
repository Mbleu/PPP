#include "..\..\std_lib_facilities.h"

int main()
{
	cout << "Please enter an integer value: ";
	int n;
	cin >> n;
	double dn = n;
	cout << "n == " << n
		<< "\nn+1 == " << n + 1
		<< "\nthree times n == " << 3 * n
		<< "\ntwice n == " << n + n
		<< "\nn squared == " << n * n
		<< "\nhalf of n == " << n / 2
		<< "\nsquare root of n == " << sqrt(dn) // through looking online, I've discovered that using the integer n directly instead of the double dn yields the same result because it gets implicitly converted into a double
		<< '\n'; // another name for newline ("end of line") in ouput
}