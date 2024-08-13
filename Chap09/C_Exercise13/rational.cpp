#include "rational.h"
#include <vector>
using namespace Rational;

// Fraction's Member Functions:
Fraction::Fraction(const int numer, const int denom)	// Constructs a fraction from a given numerator and denominator
{
	set_numer(numer);
	set_denom(denom);
}

Fraction::Fraction(const double d)	// Constructs a fraction from a given rational decimal
{
	if (INT_MIN > d || d > INT_MAX) throw Invalid("error: Rational::Fraction::Fraction(const double): received number too large");	// pre

	double numer{ d };
	int denom{ 1 };
	while (numer != int(numer)) {	// increment through denominators until corresponding numerator is also an int
		++denom;
		numer = d * denom;
		if (numer >= INT_MAX) throw Invalid("error: Rational::Fraction::Fraction(const double): numerator too large");
	}
	set_numer(int(numer));
	set_denom(denom);
}

void Fraction::set_denom(const int i)	// Check value is valid and set denominator
{
	if (i == 0) throw Invalid("error: Rational::Fraction::set_denom(const int): received denominator with value 0");	// pre
	denom = i;
}

void Fraction::simplify()	// Simplify the fraction
{
	for (int i = denom; i > 0; --i) {			// find the greatest common divisor between 2 numbers
		if (numer % i == 0 && denom % i == 0) {
			numer /= i;
			denom /= i;
			return;
		}
	}
}

// Fraction's Helper Functions:
std::ostream& Rational::operator<<(std::ostream& os, const Fraction& f) { return os << f.get_numer() << '/' << f.get_denom(); }	// Output a fraction

Fraction Rational::operator-(const Fraction& f)	// Unary minus
{
	long long numer{ -long long(f.get_numer()) };	// large container to avoid overflow
	if (INT_MIN > numer || numer > INT_MAX) throw Invalid("error: Rational::operator-(const Rational::Fraction&): numerator too large");
	return Fraction(int(numer), f.get_denom());
}

Fraction Rational::operator+(const Fraction& f1, const Fraction& f2)	// Add 2 fractions
{
	long long numer1{ long long(f1.get_numer()) * long long(f2.get_denom()) };		// large container to avoid overflow
	if (INT_MIN > numer1 || numer1 > INT_MAX) throw Invalid("error: Rational::operator+(Rational::Fraction&, Rational::Fraction&): numerator too large");

	long long numer2{ long long(f2.get_numer()) * long long(f1.get_denom()) };		// large container to avoid overflow
	if (INT_MIN > numer2 || numer2 > INT_MAX) throw Invalid("error: Rational::operator+(Rational::Fraction&, Rational::Fraction&): numerator too large");

	long long numer_final{ numer1 + numer2 };										// large container to avoid overflow
	if (INT_MIN > numer_final || numer_final > INT_MAX) throw Invalid("error: Rational::operator+(Rational::Fraction&, Rational::Fraction&): numerator too large");

	long long denom_final{ long long(f1.get_denom()) * long long(f2.get_denom()) };	// large container to avoid overflow
	if (INT_MIN > denom_final || denom_final > INT_MAX) throw Invalid("error: Rational::operator+(Rational::Fraction&, Rational::Fraction&): denominator too large");

	Fraction f_final{ int(numer_final), int(denom_final) };
	f_final.simplify();

	return f_final;
}

Fraction Rational::operator-(const Fraction& f1, const Fraction& f2) { return -f2 + f1; }	// Subtract one fraction from another

Fraction Rational::operator*(const Fraction& f1, const Fraction& f2)	// Multiply one fraction by another
{
	long long numer{ long long(f1.get_numer()) * long long(f2.get_numer()) };	// large container to avoid overflow
	if (INT_MIN > numer || numer > INT_MAX) throw Invalid("error: Rational::operator+(Rational::Fraction&, Rational::Fraction&): numerator too large");
	long long denom{ long long(f1.get_denom()) * long long(f2.get_denom()) };	// large container to avoid overflow
	if (INT_MIN > denom || denom > INT_MAX) throw Invalid("error: Rational::operator+(Rational::Fraction&, Rational::Fraction&): denominator too large");

	Fraction f{ int(numer), int(denom) };
	f.simplify();

	return f;
}

Fraction Rational::operator/(const Fraction& f1, const Fraction& f2) { return f1 * Fraction(f2.get_denom(), f2.get_numer()); }	// Divide one fraction by another

bool Rational::operator==(const Fraction& f1, const Fraction& f2)	// Determine if 2 fractions are equal
{
	if (f1.get_numer() == f2.get_numer() && f1.get_denom() == f2.get_denom()) return true;
	return false;
}

// Invalid's Helper Functions:
std::ostream& Rational::operator<<(std::ostream& os, const Invalid& inv) { return os << inv.msg; }	// Ouput an exception message