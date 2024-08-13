#include "..\..\std_lib_facilities.h"		// converts Celsius to Kelvin

double ctok(double c)
{
	double k = c + 273.15;
	return k;
}

int main()
{
	double c = 0;							// declare input variable
	cin >> c;								// retrieve temperature to input variable
	double k = ctok(c);						// convert temperature
	cout << k << '/n';						// print out temperature
}

//Faulty program
//double ctok(double c)
//{
//	int k = c + 273.15;
//	return int
//}
//
//int main()
//{
//	double c = 0;							// declare input variable
//	cin >> d;								// retrieve temperature to input variable
//	double k = ctok("c");					// convert temperature
//	Cout << k << '/n';						// print out temperature
//}

//List of fixed issues: -line 5: changed type of k from int to double
//						-line 6: replaced int with k
//						-line 6: added semi-colon after return k
//						-line 12: changed d to c
//						-line 13: changed string literal "c" to variable c
//						-line 14: changed Cout to cout