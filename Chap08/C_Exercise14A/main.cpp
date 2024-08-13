/*Program for testing use cases for const non-reference parameters.*/

#include <iostream>
using namespace std;

double ftok(const double f)    // Converts degress Fahrenheit to Kelvin
{
    return (f - 32) * 5 / 9 + 273.15;  // formula for converting Fahrenheit to Kelvin
}

int main()
try {
    double f = 45;
    cout << "F: " << f << endl << "K: " << ftok(f) << endl;
}
catch (...) {
    return 1;
}