#include "..\..\std_lib_facilities.h"

int main()
{
	cout << "Please enter three string values separated by spaces (followed by 'enter'):\n";
	string val1 = " ";
	string val2 = " ";
	string val3 = " ";
	string valTemp = " ";
	cin >> val1 >> val2 >> val3;

	//Correctly order values 1 and 2
	//Note there is no code for if they are equal or if value 1 is smaller since either way the current order would be correct
	if (val2 < val1) {
		valTemp = val1;
		val1 = val2;
		val2 = valTemp;
	}

	//If value 3 is less than the other two then put it at the start and budge the other two along
	//Note there is no code for if they are equal since if they are then the next "if" would put value 3 in the middle anyway
	if (val3 < val1) {
		valTemp = val1;
		val1 = val3;
		val3 = val2;
		val2 = valTemp;
	}

	//If value 3 is less than value 2 then put it in the middle and budge value 2 along
	//Note that we won't go into this "if" if we went into the previous "if". This is because everything would already be in the correct order so value 3 would not evaluate as less than value 2
	//Note there is no code for if they are equal since if they are then they are already next to each other
	//Note that if all three values are equal then it doesn't matter where anything ends up so we don't need to worry
	if (val3 < val2) {
		valTemp = val2;
		val2 = val3;
		val3 = valTemp;
	}

	cout << "The values in alphanumerical sequence are: " << val1 << ", " << val2 << ", " << val3;
}