#include "..\..\std_lib_facilities.h"

int main()
{
	vector<double> temps;					// temperatures

	for (double temp; cin >> temp;)			// read and put into temps
		temps.push_back(temp);

	double sum = 0;
	double high_temp = 0;
	double low_temp = 0;

	for (int x : temps)
	{
		if (x > high_temp) high_temp = x;	// find high
		if (x < low_temp) low_temp = x;		// find low
		sum += x;							// compute sum
	}

	cout << "High temperature: " << high_temp << '\n';
	cout << "Low temperature: " << low_temp << '\n';
	cout << "Average temperature: " << sum/temps.size() << '\n';
}

// the least amount on input required to break the program is none at all

// problems with this program:
// 1) if all temps are above 0, the low temp will remain 0 and be wrong
// 2) if all temps are below 0, the high temp will remain 0 and be wrong
// 3) the range loop uses an int instead of a doulbe which causes narrowing errors for floating point numbers
// 4) the program is not protected from erroneous input from the user