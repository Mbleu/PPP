#include "..\..\std_lib_facilities.h"

int main()
{
	vector<double> temps;			// temperatures
	for (double temp; cin >> temp;)	// read into temp
		temps.push_back(temp);		// put temp into vector

	// compute mean temperature:
	double sum = 0;
	for (int x : temps) sum += x;
	cout << "Average temperature: " << sum / temps.size() << '\n';

	// compute median temperature:
	sort(temps);					// sort temperatures
	if (temps.size() % 2 == 1) {	// when vector has odd number of elements
		double median = temps[temps.size() / 2];
		cout << "Median temperature: " << median;
	}
	else {							// when vector has even number of elements
		double below_med{ temps[temps.size() / 2 - 1] };
		double above_med{ temps[temps.size() / 2] };
		double med_delta{ above_med - below_med };
		double median{ below_med + med_delta / 2 };
		cout << "Median temperature: " << median;
	}
}