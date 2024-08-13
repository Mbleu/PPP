/*Program that finds the largest element of a vector.*/

#include <vector>
#include <iostream>
using namespace std;

double maxv(const vector<double>& v)	// Returns the largest element of a vector
{
	if (v.size() == 0) throw exception("error: maxv: received vector of size 0");	// pre: vector must have at least one element
	double max{v[0]};
	for (double d : v)
		if (d > max) max = d;

	return max;
}

int main()
try {
	vector<double> v{ 5, 2, -1, 0.0, 0.32, 6.3, -2 };	// example vector
	cout << maxv(v);
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	return 2;
}