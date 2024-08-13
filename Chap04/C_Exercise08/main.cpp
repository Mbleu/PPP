#include "..\..\std_lib_facilities.h"

int main()
{
	int grains{ 1 };
	int sum{ grains };

	cout << "There is an old story that the emperor wanted to thank the inventor of the game of chess and asked the inventor to name his reward. "
		<< "The inventor asked for one grain of rice for the first square, 2 for the second, 4 for the third, and so on, doubling for each of the 64 squares.\n";

	cout << "On square 1 there is " << grains << " grain of rice. The total amount of rice so far is " << sum << " grain.\n";
	for (int square{ 2 }; sum < 1000000000; ++square) {
		grains *= 2;
		sum += grains;
		cout << "On square " << square << " there are " << grains << " grains of rice. The total amount of rice so far is " << sum << " grains.\n";
	}
}