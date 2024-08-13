/*	
	This is a rewrite of Exercise 7 from Chapter 5 to include rules learnt in Chapter 7.
	Last updated 26/04/23 by William Falcon-Uff
	This program solves quadratic equations.
*/

#include "..\..\std_lib_facilities.h"

bool check_roots(double a, double b, double c, vector<double> roots)	// Checks that roots of a quadratic are correct.
{
	for (double root : roots)
		if (a * pow(root, 2) + b * root + c != 0) ("error: check_roots: incorrect root");

	return true;
}

vector<double> solve_quad(double a, double b, double c)	// Solves quadratics. Takes 3 coefs and returns roots.
{
	vector<double> roots;

	double dis = pow(b, 2) - 4 * a * c;										// calculate the discriminant

	if (dis > 0) {															// there are two real roots
		roots.push_back((-b + sqrt(dis)) / (2 * a));
		roots.push_back((-b - sqrt(dis)) / (2 * a));
	}
	else if (dis == 0) roots.push_back(-b / (2 * a));						// there is one real root
	else error("error: solve_quad: set of coefficients has no real roots");	// post: must be at least one real root

	check_roots(a, b, c, roots);											// post: roots must be correct
	return roots;
}

void clear_is()	// Discards input up to and including the next newline.
{
	while (cin.get() != '\n');
	return;
}

int main()
try {
	cout << "Enter values for a, b and c of a quadratic equation of the form ax^2 + bx + c = 0 to solve for x.\n";

	while (1) try {
		cout << "> ";																								// prompt user

		double a = 0, b = 0, c = 0;

		if (!(cin >> a >> b >> c) || cin.peek() != '\n') error("error: main: invalid input for a, b and c");

		vector<double> roots = solve_quad(a, b, c);

		for (int i = 0; i < roots.size(); i++)
			cout << 'x' << i + 1 << " = " << roots[i] << '\n';
	}
	catch (runtime_error& e) {																						// handles errors related to erroneous input
		cerr << e.what() << endl;
		cin.clear();
		clear_is();
	}
}
catch (...) {																										// handles fatal exceptions
	cerr << "exception\n";
	return 1;
}