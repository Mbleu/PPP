#pragma once
#include <vector>
#include <string>
#include "..\..\std_lib_facilities.h"

namespace Roman
{
	class Number {	// An integer number represented in roman numeral form (1-3999)
	public:
		Number(const unsigned int i) { set_val(i); }
		void set_val(const unsigned int val);
		int as_int() const { return val; }	// Return roman number as an integer
		std::string as_numeral() const;	// return roman number as numeral

	private:
		unsigned int val;
	};

	// Custom exceptions:
	struct Invalid : public std::runtime_error {
		Invalid(const std::string& msg) : std::runtime_error(msg) {}
	};

	// Number Helper Functions:
	unsigned int to_int(std::string s_num);							// convert numeral to an int (returns 0 if passed invalid numeral)
	std::string to_numeral(unsigned int i_num);						// convert an int to numeral
	std::istream& operator>>(std::istream& is, Number& n);			// input a roman number as either int or numeral, reads up to the next newline
	std::ostream& operator<<(std::ostream& os, const Number& n);	// output a roman number as numeral
}