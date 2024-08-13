#include <iostream>
using namespace std;

int main()
{
	constexpr int age{ 25 };
	constexpr int birthyear{ 1998 };

	cout << "Age" << "\tYoB" << "\tNumbering System\n"	// table headers
		<< "--------------------------------\n"
		<< age << '\t' << birthyear << "\tDecimal\n"
		<< hex << age << '\t' << birthyear << "\tHexadecimal\n"
		<< oct << age << '\t' << birthyear << "\tOctal\n";
}