#include "..\..\std_lib_facilities.h"

int main()
{
	double grains{ 1 };
	double sum{ grains };

	cout << "There is an old story that the emperor wanted to thank the inventor of the game of chess and asked the inventor to name his reward. "
		<< "The inventor asked for one grain of rice for the first square, 2 for the second, 4 for the third, and so on, doubling for each of the 64 squares.\n";

	//cout.precision(17);
	cout << "On square 1 there is " << grains << " grain of rice. The total amount of rice so far is " << sum << " grain.\n";
	for (int square{ 2 }; square <=1025; ++square) {
		grains *= 2;
		sum += grains;
		cout << "On square " << square << " there are " << grains << " grains of rice. The total amount of rice so far is " << sum << " grains.\n";
	}

	// when a number becomes too large to represent as an int, it wraps back around to the lowest negative value for an int and keeps counting from there
	// when a number becomes too large to represent exactly as a double, it gives an approximate value instead and uses scientific notation for order of magnitude
	// the largest number of squares for which the exact number of grains can be calculated using an int is 31
	// the largest number of squares for which an approximate number of grains can be calculated using a double is 1024, although for the total sum of grains so far this is 1023
}