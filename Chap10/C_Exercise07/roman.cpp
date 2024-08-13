#include "roman.h"
#include <iostream>
using namespace Roman;
using namespace std;

// Numeral tables
const vector<string> units{ "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };		// numerals representing 1-9 for each decimal place
const vector<string> tens{ "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };		// there is no concept of 0
const vector<string> hundreds{ "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };	// a valid numeral is made by appending up to one numeral from each
const vector<string> thousands{ "M", "MM", "MMM" };
const vector<vector<string>>& dec_places{ units, tens, hundreds, thousands };				// combines tables for easy searches
constexpr unsigned int max_num{ 3999 };														// max numeral value

// Number Member Functions:
void Number::set_val(const unsigned int val)
{
	if (val == 0) throw Invalid("Roman::Number::set_val(const unsigned int): value can't be 0");				// pre
	if (val > max_num) throw Invalid("Roman::Number::set_val(const unsigned int): received int too large");	// pre
	this->val = val;
}

string Number::as_numeral() const { return to_numeral(val); }	// Return roman number as numeral

// Number Helper Functions:
unsigned int ipow(const unsigned int base, const unsigned int exponent)	// Integer version of pow()
{
	unsigned int result{ 1 };
	for (int i = 0; i < exponent; ++i)
		result *= base;
	return result;
}

unsigned int Roman::to_int(string s_num)	// Convert numeral to an int
{
	if (s_num.empty()) throw Invalid("Roman::to_int(const string&): received empty string");	// pre

	unsigned int i_num{ 0 };

	for (int i = int(dec_places.size()); i > 0; --i)												// search the decimal place tables from highest to lowest
		for (int j = int(dec_places[i - 1].size()); j > 0; --j)										// search current decimal place numerals from the highest to lowest
			if (s_num.compare(0, dec_places[i - 1][j - 1].size(), dec_places[i - 1][j - 1]) == 0) {	// does the start of the input numeral match the current numeral
				i_num += ipow(10, i - 1) * j;														// add the value of the current numeral (e.g. 900 = 10^2 * 9)
				s_num.erase(0, dec_places[i - 1][j - 1].size());									// erase from the start of the input numeral, the current numeral
				break;
			}

	if (!s_num.empty()) throw Invalid("Roman::to_int(const string&): received invalid numeral");	// post: numeral couldn't be converted
	return i_num;
}

string Roman::to_numeral(unsigned int i_num)	// Convert an int to numeral
{
	if (i_num == 0) throw Invalid("error: Roman::to_numeral(unsigned int): cannot convert 0 to numeral");							// pre
	if (i_num > max_num) throw Invalid("error: Roman::to_numeral(unsigned int): received int too large to convert to numeral");	// pre

	string s_num;
	for (int i = dec_places.size(); i > 0; --i) {													// check each decimal place, highest to lowest
		if (i_num / ipow(10, i - 1) != 0) s_num += dec_places[i - 1][i_num / ipow(10, i - 1) - 1];	// how many of this decimal place, append the numeral
		i_num %= ipow(10, i - 1);
	}

	return s_num;
}

istream& Roman::operator>>(istream& is, Number& n)	// Input a roman number as either int or numeral, reads up to the next newline
{
	unsigned int i_num{ 0 };
	if (!(is >> i_num)) try {							// if not already an integer, convert numeral to int
		is.clear();
		string s_num;
		if (is >> s_num) i_num = to_int(s_num);
	}
	catch (Invalid& e) { is.clear(ios_base::failbit); }	// input numeral was invalid, fail

	if (is.peek() != '\n') is.clear(ios_base::failbit);	// if more than one number was input, fail

	if (!is.fail()) try { n.set_val(i_num); }			// if no problems reading, set the value
	catch (Invalid& e) { is.clear(ios_base::failbit); }	// input integer was invalid, fail

	return is;
}

std::ostream& Roman::operator<<(std::ostream& os, const Number& n) { return os << n.as_numeral(); }	// Output a roman number as numeral