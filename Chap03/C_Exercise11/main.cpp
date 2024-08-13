#include "..\..\std_lib_facilities.h"

int main()
{
	cout << "Please enter a number of pennies (followed by 'enter'):\n";
	int pennies;
	cin >> pennies;
	cout << "Please enter a number of nickels (followed by 'enter'):\n";
	int nickels;
	cin >> nickels;
	cout << "Please enter a number of dimes (followed by 'enter'):\n";
	int dimes;
	cin >> dimes;
	cout << "Please enter a number of quarters (followed by 'enter'):\n";
	int quarters;
	cin >> quarters;
	cout << "Please enter a number of half-dollars (followed by 'enter'):\n";
	int halves;
	cin >> halves;
	cout << "Please enter a number of dollars (followed by 'enter'):\n";
	int dollars;
	cin >> dollars;

	int totPennies = pennies + 5 * nickels + 10 * dimes + 25 * quarters + 50 * halves + 100 * dollars;

	if (pennies == 1) {
		cout << "You have " << pennies << " penny.\n";
	}
	else {
		cout << "You have " << pennies << " pennies.\n";
	}
	if (nickels == 1) {
		cout << "You have " << nickels << " nickel.\n";
	}
	else {
		cout << "You have " << nickels << " nickels.\n";
	}
	if (dimes == 1) {
		cout << "You have " << dimes << " dime.\n";
	}
	else {
		cout << "You have " << dimes << " dimes.\n";
	}
	if (quarters == 1) {
		cout << "You have " << quarters << " quarter.\n";
	}
	else {
		cout << "You have " << quarters << " quarters.\n";
	}
	if (halves == 1) {
		cout << "You have " << halves << " half-dollar.\n";
	}
	else {
		cout << "You have " << halves << " half-dollars.\n";
	}
	if (dollars == 1) {
		cout << "You have " << dollars << " dollar.\n";
	}
	else {
		cout << "You have " << dollars << " dollars.\n";
	}
	cout << "You have " << totPennies << " cents in total.\n";
	cout << "You have " << totPennies / 100 << " dollars and " << totPennies % 100 << " cents in total.\n";

}