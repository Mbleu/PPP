/*Sums all the whitespace-separated integers in a text file.*/

#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	ifstream ifs{ "integers.txt" };

	int sum{ 0 };
	int i;
	string discard;
	while (!ifs.eof()) {				// read until end of file
		if (ifs >> i) sum += i;			// if its an int, sum it
		else {							// otherwise discard up to next whitespace
			ifs.clear();
			ifs >> discard;
		}
	}
	cout << sum;
}