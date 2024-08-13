#include "..\..\std_lib_facilities.h"

vector<double> quadratic(double a, double b, double c)	// solves quadratic equations using the quadratic formula
{
	vector<double> solutions;
	double x1{ 0 };
	double x2{ 0 };

	x1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);		// quadratics with no solution will attempt to calulate the squareroot of a negative value and will fail
	x2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

	solutions.push_back(x1);
	solutions.push_back(x2);

	return solutions;
}

int main()
{
	double a{ 0 }, b{ 0 }, c{ 0 };
	vector<double> solutions;

	cout << "Enter a value for 'a', 'b' and 'c' respectively separated by spaces to solve a quadratic equation of the form ax^2 + bx + c = 0 (followed by 'enter'):\n";

	if (cin >> a >> b >> c) {
		solutions = quadratic(a, b, c);
		for (int i{ 0 }; i < solutions.size(); ++i)
			cout << 'x' << i + 1 << " = " << solutions[i] << '\n';
	}

}