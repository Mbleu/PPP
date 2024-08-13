/* Program for storing rational numbers as fractions and manipulating them.*/

#include "rational.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

int main()	// Test the Rational class
try {
	double large{ 10000000000 };		// 10 billion, too large for an int to store

	// Constructors:
	Rational::Fraction r0{ 10, 2 };		// valid integers
	Rational::Fraction r1{ 0, 2 };		// valid integers, zero numerator
	//Rational::Fraction r2{ 2, 0 };	// invalid integers, zero denominator
	Rational::Fraction r3{ 1, 100 };	// valid integers, one numerator
	Rational::Fraction r4{ 100, 1 };	// valid integers, one denominator

	Rational::Fraction r5{ 342.62365 };	// valid decimal
	Rational::Fraction r6{ 0.0 };		// valid decimal, zero
	Rational::Fraction r7{ 1.0 };		// valid decimal, one
	//Rational::Fraction r8{ large };	// invalid decimal, too large
	//Rational::Fraction r9{ -large };	// invalid decimal, too small

	Rational::Fraction r10{ };			// default

	cout << r0 << endl << r1 << endl << r3 << endl << r4 << endl << r5 << endl << r6 << endl << r7 << endl << r10 << endl << endl;

	// Member functions:
	cout << double(r5) << endl;

	r0.simplify();
	cout << r0 << endl << endl;

	// Helper functions:
	cout << -r0 << endl;
	cout << Rational::Fraction(233, 47) + Rational::Fraction(12, 46) << endl;
	cout << Rational::Fraction(233, 47) - Rational::Fraction(12, 46) << endl;
	cout << Rational::Fraction(10, 2) * Rational::Fraction(7, 9) << endl;
	cout << r0 / r0 << endl;
	cout << (r0 == r0) << endl;
}
catch (const Rational::Invalid& ri) {
	cerr << ri << endl;
	return 1;
}
catch (const std::exception& e) {
	cerr << e.what() << endl;
	return 2;
}
catch (...) {
	cerr << "Fatal unknown error." << endl;
	return 3;
}