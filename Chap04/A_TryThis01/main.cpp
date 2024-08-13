#include "..\..\std_lib_facilities.h"

// convert from yen, euro, pounds, yuan and kroner to dollar
// a suffix 'y', 'e', 'p', 'j' and 'k' indicates the currency of the input
// any other suffix is an error
int main()
{
	constexpr double yen_to_dol = 0.0068;
	constexpr double eur_to_dol = 1.01;
	constexpr double poun_to_dol = 1.16;
	constexpr double yua_to_dol = 0.14;
	constexpr double kron_to_dol = 0.098;

	double amount = 0;
	char curr = ' ';

	cout << "Please enter an amount followed by a currency ('y' for yen, 'e' for euro, 'p' for pounds, 'j' for yuan, 'k' for kroner):\n";
	cin >> amount >> curr;

	if (curr == 'y')
		cout << amount << "yen == " << yen_to_dol * amount << "dollars\n";
	else if (curr == 'e')
		cout << amount << "euro == " << eur_to_dol * amount << "dollars\n";
	else if (curr == 'p')
		cout << amount << "pounds == " << poun_to_dol * amount << "dollars\n";
	else if (curr == 'j')
		cout << amount << "yuan == " << yua_to_dol * amount << "dollars\n";
	else if (curr == 'k')
		cout << amount << "kroner == " << poun_to_dol * amount << "dollars\n";
	else
		cout << "Sorry, I don't know a curreny called '" << curr << "'.\n";
}