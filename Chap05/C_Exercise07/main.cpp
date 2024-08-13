// Program for solving quadratic equations
// Root solutions are checked by the use of the check_roots function which plugs the values back into the quadratic equation to see if the results are equal(or almost!) to 0

#include "..\..\std_lib_facilities.h"

// two doubles to hold quadratic roots
// bool flag to remember if there is only one root, this is used to avoid comparing floating point values for equality which can be problematic due to minor imprecisions
struct Roots{
	double x1 = 0;
	double x2 = 0;
	bool sing_root = false;
};

bool check_roots(double a, double b, double c, Roots roots)			// checks that the roots for a quadratic equation are correct to within a margin of error
{
	constexpr double error_margin = 0.0001;							// this margin of error is necessary due to the inprecision of floating point number operations

	if (a * (roots.x1 * roots.x1) + b * roots.x1 + c > error_margin)		// x1 is incorrect
		error("error: check_roots: incorrect root x1");

	if (!roots.sing_root)
		if (a * (roots.x2 * roots.x2) + b * roots.x2 + c > error_margin)	// x2 is incorrect
			error("error: check_roots: incorrect root x2");

	return true;
}

// preconditions: that it receives 3 doubles which is checked by type rules automatically
// postconditions: -there must be at least one real root, which is checked by making sure the discriminant isn't less than 0
//					-the check_roots function is called
Roots solve_quad(double a, double b, double c)
{
	Roots roots;

	double dis = b*b - 4*a*c;								// calculate the discriminant

	if (dis > 0) {											// there are two real roots
		roots.x1 = (-b + sqrt(dis)) / (2*a);				
		roots.x2 = (-b - sqrt(dis)) / (2*a);
	}
	else if (dis == 0) {									// there is one real root
		roots.x1 = -b / (2 * a);
		roots.x2 = roots.x1;								// this is not really needed since there is only one distinct real root, however it is safer than leaving it erroneously on 0
		roots.sing_root = true;
	}
	else													// there are no real roots
		error("error: solve_quad: set of coefficients has no real roots");

	check_roots(a, b, c, roots);							// no if statement here since the function handles its own errors

	return roots;
}

int main()
try {
	cout << "Enter values for a, b and c of a quadratic equation of the form ax^2 + bx + c = 0 to solve for x.\n";

	double a = 0;
	double b = 0;
	double c = 0;

	if (!(cin >> a >> b >> c))
		error("error: values for a, b and c not entered");

	Roots roots = solve_quad(a, b, c);

	if (roots.sing_root)									// appropriate output to stream depending on many roots
		cout << "x1 = " << roots.x1 << '\n';
	else
		cout << "x1 = " << roots.x1 << "\nx2 = " << roots.x2;
}
catch (exception& e) {
	cerr << e.what();
}