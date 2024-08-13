#include "..\..\std_lib_facilities.h"

int main()
{
	vector<double> dists;
	double dist{ 0 };
	double sum{ 0 };
	double shortest{ 0 };
	double longest{ 0 };

	cout << "Enter the distances between each city on your route separated by spaces (followed by 'enter'):\n";
	while (cin >> dist)
		dists.push_back(dist);

	shortest = longest = dists[0];	// sets the shortest and longest distance to one of the distances so they have something to begin comparing to
	for (double d : dists) {		// iterates through all the distances
		sum += d;					// sums all the distances
		if (d < shortest)			// if distance is shorter, then assign to shortest
			shortest = d;
		if (d > longest)			// if distance is longer, then assign to longest
			longest = d;
	}

	cout << "The total distance is: " << sum
		<< "\nThe shortest distance between two neighboring cities is: " << shortest << "\nThe longest distance between two neighboring cities is: " << longest
		<< "\nThe mean distance between two neighboring cities is: " << sum / dists.size();
}