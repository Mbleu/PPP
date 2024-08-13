#include "..\..\std_lib_facilities.h"

int main()
{
	cout << "Please enter two integer values separated by a 'space' (followed by 'enter'):\n";
	int val1 = 0;
	int val2 = 0;
	cin >> val1 >> val2;

	if (val1 < val2) {
		cout << "The smaller number is: " << val1 << "\nThe larger number is: " << val2 << '\n';
	}
	if (val2 < val1) {
		cout << "The smaller number is: " << val2 << "\nThe larger number is: " << val1 << '\n';
	}
	if (val1 == val2) {
		cout << "The numbers " << val1 << " and " << val2 << ", are equal.\n";
	}

	cout << "The sum of " << val1 << " and " << val2 << " is: " << val1 + val2 << '\n';

	cout << "The difference between " << val1 << " and " << val2 << " is: " << val1 - val2 << '\n';

	cout << "The product of " << val1 << " and " << val2 << " is: " << val1 * val2 << '\n';

	cout << "The ratio of " << val1 << " to " << val2 << " is: " << val1 / val2 << '\n';
}