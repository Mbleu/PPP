#include "patron.h"
#include <iostream>
#include <string>
using namespace std;

// Helper function:

bool is_debt(const Patron& patron) { if (patron.get_balance() < 0) return true; else return false; }	// Check if the patron owes fees

std::ostream& operator<<(std::ostream& os, const Patron& patron)	// Operator for outputting a patron's name, library card number and account balance
{
	return os << "Name: " << patron.get_name() << endl 
		<< "Library card number: " << patron.get_lib_card() << endl
		<< "Account balance: " << patron.get_balance() << endl;
}