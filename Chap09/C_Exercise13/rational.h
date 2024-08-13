#pragma once
#include <iostream>

namespace Rational
{
	class Fraction // For storing and manipulating numbers as fractions
	{
	public:
		Fraction(const int numer, const int denom);	// constructs a fraction from a given numerator and denominator
		Fraction(const double d);					// constructs a fraction from a given rational decimal
		Fraction() {}								// constructs a fraction with the default values

		int get_numer() const { return numer; }
		int get_denom() const { return denom; }
		void set_numer(const int i) { numer = i; }
		void set_denom(const int i);				// check value is valid, set denominator

		void simplify();							// simplify the fraction
		operator double() { return double(numer) / double(denom); }	// Convert a fraction to a double

	private:
		int numer{ 0 };
		int denom{ 1 };
	};
	// Fraction's Helper Functions:
	std::ostream& operator<<(std::ostream& os, const Fraction& f);	// output a fraction
	Fraction operator-(const Fraction& f);							// unary minus
	Fraction operator+(const Fraction& f1, const Fraction& f2);		// add 2 fractions
	Fraction operator-(const Fraction& f1, const Fraction& f2);		// subtract one fraction from another
	Fraction operator*(const Fraction& f1, const Fraction& f2);		// multiply one fraction by another
	Fraction operator/(const Fraction& f1, const Fraction& f2);		// divide one fraction by another
	bool operator==(const Fraction& f1, const Fraction& f2);		// determine if 2 fractions are equal

	struct Invalid	// For throwing exceptions
	{	
		const std::string msg;							// error message
		Invalid(const std::string& msg) : msg(msg) {}
	};
	// Invalid's Helper Functions:
	std::ostream& operator<<(std::ostream& os, const Invalid& inv);	// ouput an exception message
}