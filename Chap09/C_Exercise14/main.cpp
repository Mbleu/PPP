/*Program for storing amounts of money in their associated currencies and manipulating them.*/

#include <iostream>
using namespace std;

struct Currency
{
	const string name;
	const string ISO;																				// standard alpha code for a currency (e.g. USD)
	const char symbol;
	const unsigned int utomu;																		// number of units to a main unit (e.g. cents to a euro)

	Currency(const string& name, const string& ISO, const char symbol, const unsigned int utomu)
		: name(name), ISO(ISO), symbol(symbol), utomu(utomu) {}
};

class Money
{
public:
	const Currency cur;
	int units{ 0 };

	Money(Currency c, const double m_units)
		: cur(c)
	{
		const double units{ m_units * c.utomu };				// total in units (main unit = euro, pound, etc.	unit = cent, penny, etc.)
		const int whole_units{ int(units) };					// total in units minus the partial unit
		const double part_units{ units - double(whole_units) };	// the remaining partial unit
		bool round_up{ false };
		if (part_units >= 0.5) round_up = true;					// round up the partial unit if its 0.5 of a unit or more
		this->units = whole_units + round_up;
	}

	double m_units() const { return double(units) / cur.utomu; }		// returns the amount of units in main units
};
// Money Helper Functions:
std::ostream& operator<<(std::ostream& os, const Money& m)
{
	return os << m.cur.ISO << double(m.units) / m.cur.utomu;
}

struct Invalid_input	// For throwing exceptions
{
	std::istream& is;																// reference to input stream so it can be passed on to be cleared
	const std::string msg;															// error message
	Invalid_input(std::istream& is, const std::string& msg) : is(is), msg(msg) {}
};
std::istream& operator>>(std::istream& is, Money& m)
{
	while (is.peek() == ' ' || is.peek() == '	' || is.peek() == '\n') is.get();	// ignore whitespace

	string ISO;
	for (int i = 0; i < m.cur.ISO.size(); ++i) {									// get the first few characters for ISO comparison
		ISO += is.get();
	}
	if (m.cur.ISO != ISO) throw Invalid_input(is, "error: operator>>(std::istream&, const Money&): currencies don't match");
	
	double m_units;
	if (!(is >> m_units) || is.peek() != '\n') throw Invalid_input(is, "error: operator>>(std::istream&, const Money&): invalid amount");
	m.units = m_units * m.cur.utomu;												// set new amount of units
	return is;
}

Money operator+(const Money& m1, const Money& m2)
{
	if (m1.cur.ISO != m2.cur.ISO) throw exception("error: operator+(const Money&, const Money&): currencies don't match");	// pre

	return Money(m1.cur, m1.m_units() + m2.m_units());
}
Money operator-(const Money& m1, const Money& m2)
{
	if (m1.cur.ISO != m2.cur.ISO) throw exception("error: operator+(const Money&, const Money&): currencies don't match");	// pre

	return Money(m1.cur, m1.m_units() - m2.m_units());
}
Money operator+(const Money& m, const double d) { return Money(m.cur, m.m_units() + d); }
Money operator-(const Money& m, const double d) { return Money(m.cur, m.m_units() - d); }
Money operator*(const Money& m, const double d) { return Money(m.cur, m.m_units() * d); }
Money operator/(const Money& m, const double d) { return Money(m.cur, m.m_units() / d); }


int main()	// Test the Money and Currency classes
try {
	Currency dollar{ "United Sates dollar", "USD", '$', 100 };									// Examples of currencies
	Currency pound{ "Sterling", "GBP", '£', 100 };
	Currency euro{ "euro", "EUR", '€', 100 };
	Currency galleon{ "Wizarding Golden Galleon", "WGG", 'G', 493 };							// There are 493 Knuts to a Galleon

	Money m1{ dollar, 123.455452352 };															// Examples of monies
	Money m2{ dollar, 127.425452352 };
	cout << "Money1: " << m1 << endl 
		<< "Money2: " << m2 << endl 
		<< "M1 - M2 = " << m1 - m2 << endl;

	cout << "Please enter a new amount for M1 in the form, " << m1.cur.ISO << "0.0:" << endl;
	while (1) try {																				// Loop until a valid amount is entered
		cout << ">";
		cin >> m1;
		break;
	}
	catch (Invalid_input& ii) {																	// Report error, reset and discard invalid input
		cerr << ii.msg << endl;
		ii.is.clear();
		while (ii.is.get() != '\n');
	}
	cout << "M1 = " << m1 << endl;
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	cerr << "Unknown fatal exception." << endl;
	return 2;
}