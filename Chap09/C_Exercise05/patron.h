#pragma once
#include <string>
#include <iostream>

class Patron {
public:
	Patron(std::string name, int lib_card) : name(name), lib_card(lib_card) {}
	std::string get_name()const { return name; }
	int get_lib_card()const { return lib_card; }
	double get_balance()const { return balance; }
	void set_balance(double val) { balance += val; }							// alter the balance of the account by a given amount
	
private:
	std::string name;
	int lib_card;																// library card number
	double balance{ 0 };														// monetary balance, negative if fees are owed
};

// Helper functions:
bool is_debt(const Patron& patron);	// check if the patron owes fees
std::ostream& operator<<(std::ostream& os, const Patron& patron);	// operator for outputting a patron's name, library card number and account balance