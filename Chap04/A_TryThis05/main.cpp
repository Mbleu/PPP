#include "..\..\std_lib_facilities.h"

int square(const int x)
{
	int x2 = 0;	// x2 is the value we will modify that will become the square of x
	for (int i = 0; i < x; ++i)
		x2 += x;

	return x2;
}

int main()
{
	int i = 0;
	while (i < 100) {
		cout << i << '\t' << square(i) << '\n';
		++i;
	}
}