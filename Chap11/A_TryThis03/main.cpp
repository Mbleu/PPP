#include <iostream>
using namespace std;

int main()
{
	double d{ 1234567.89 };
	cout << defaultfloat << d << '\t' << fixed << d << '\t' << scientific << d;
}