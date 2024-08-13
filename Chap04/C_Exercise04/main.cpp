#include "..\..\std_lib_facilities.h"

// I realised while writing this that it is in fact a binary search algorithm.

int main()
{
	int num{ 0 };
	int min{ 1 };
	int max{ 100 };
	char reply{ ' ' };

	cout << "Choose a number from 1-100 (followed by 'enter'):\n";

	if (cin >> num && num >= 1 && num <= 100) {
		while (min != max) {
			cout << "Is your number greater than " << min + (max - min) / 2 << "? Type 'y' or 'n' (followed by 'enter'):\n";
			cin >> reply;
			switch (reply) {
			case 'y':
				min = min + (max - min) / 2 + 1;
				break;
			case 'n':
				max = min + (max - min) / 2;
				break;
			default:
				cout << reply << " isn't a 'y' or 'n' answer.\n";
				break;
			}
		}
		cout << "Your number is " << min << ".\n";
	}
}