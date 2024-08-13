#include "..\..\std_lib_facilities.h"

int main()
{
	constexpr double abs_zero_f{ -459.67 };			// the coldest possible temperature in degrees farenheit
	constexpr double hot_temp_earth{ 134 };			// the hottest weather temperature ever recorded on Earth

	double sum = 0;
	double high_temp = abs_zero_f;					// a good starting point since no value can be colder
	double low_temp = hot_temp_earth * 2;			// a good starting point since twice the hottest temp ever will cover any weather on Earth
	int no_of_temps = 0;

	for (double temp; cin >> temp;) {				// read temp
		++no_of_temps;								// count temperatures
		sum += temp;								// compute sum
		if (temp > high_temp) high_temp = temp;		// find high
		if (temp < low_temp) low_temp = temp;		// find low
	}

	if (no_of_temps != 0) {
		cout << "High temperature: " << high_temp << '\n';
		cout << "Low temperature: " << low_temp << '\n';
		cout << "Average temperature: " << sum / no_of_temps << '\n';
	}
	else
		cout << "No temperatures entered!";
	
}

// the program is now geared to handle any possible weather temperature on Earth, however it has limits
// for example: temperatures on the sun, measuring temperatures not related to weather, ...