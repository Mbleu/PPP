/*Program that finds the largest and smallest elements of a vector, as well as the mean and median.*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

double calc_mean(const vector<double>& v)	// Returns the mean of a vector
{
	if (v.size() == 0) throw exception("error: calc_mean: received vector of size 0");	// pre: vector must have at least one element

	double sum{ 0 };
	for (double d : v)
		sum += d;
	return sum / v.size();
}

double calc_median(vector<double> v)	// Returns the median of a vector without altering the original
{
	if (v.size() == 0) throw exception("error: calc_median: received vector of size 0");	// pre: vector must have at least one element

	sort(v.begin(), v.end());

	if (v.size() % 2 != 0)																	// off number of elements
		return v[v.size() / 2 - 1];
	else {																					// even number of elements
		double median1 = v[v.size() / 2 - 1];
		double median2 = v[v.size() / 2];
		return (median1 + median2) / 2;														// return a value half way between the 2 medians
	}
}

struct Infov {	// Holds vector info
	double max{ 0 };
	double min{ 0 };
	double mean{ 0 };
	double median{ 0 };
};

Infov get_infov(const vector<double>& v)	// Returns the largest and smallest elements of a vector, as well as the mean and median
{
	if (v.size() == 0) throw exception("error: get_infov: received vector of size 0");	// pre: vector must have at least one element

	Infov infov;

	infov.max = v[0];
	infov.min = v[0];
	for (double d : v) {
		if (d > infov.max) infov.max = d;
		if (d < infov.min) infov.min = d;
	}

	infov.mean = calc_mean(v);
	infov.median = calc_median(v);

	return infov;
}

int main()
try {
	vector<double> v{ 5, 2, -1, 0.0, 0.32, 6.3, -2 };																								// example vector
	Infov infov = get_infov(v);
	cout << "Max: " << infov.max << endl << "Min: " << infov.min << endl << "Mean: " << infov.mean << endl << "Median: " << infov.median << endl;
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	return 2;
}