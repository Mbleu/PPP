/*Produces the sum of all numbers in a file of whitespace separated integers.*/

#include <fstream>
#include "..\..\std_lib_facilities.h"
using namespace std;

int main()
try {
	string filename{ "mydata.txt" };
	ifstream ifs{ filename };													// create file input stream and open file
	if (!ifs) error("error: main(): failed to open file ", filename);

	int sum{ 0 };
	while (ifs.good()) {														// loop while istream has no flags set
		int i;
		if (ifs >> i) sum += i;													// if int is successfully read, add it to the sum
	}
	if (ifs.bad()) error("error: main(): could not read ", filename);
	else if (ifs.fail()) error("error: main(): invalid input from ", filename);
	else if (ifs.eof()) ifs.clear();											// success, eof reached, clear istream flag for reuse

	cout << "Sum of integers from " << filename << ": " << sum << endl;
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}