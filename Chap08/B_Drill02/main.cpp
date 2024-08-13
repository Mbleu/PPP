#include "..\..\std_lib_facilities.h"

// Functions that won't compile: - swap_cr() won't compile since its argument are const-references and it attempts to change them
//
// Calls that won't compile: - swap_r: - All calls involving literals fail to compile since you cannot change the value of a literal.
//										- Calls with cx and cy as arguments fail to compile since the function cannot channge the value of a constant.
//										- Call with dx and dy fail to compile since swap_r only accepts references to integers as arguments.
//											The compiler cannot perform an implicit conversion to double as it would in the case of an argument passed by value
//											since no new variable copy is being made here.
// 
// Test Results:	swap_v: - All calls compiled, however none had any effect on the original variables, constants and literals.
//								This is because the function takes copies of objects as arguments and changes those. It therefore never affects the original objects.
//					swap_r: - swap_r(x, y) then is the only function call that both compiled and performed as advertised.			

void swap_v(int a, int b)	// swap values of arguments passed by value
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

void swap_r(int& a, int& b)	// swap values of arguments passed by reference
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

//void swap_cr(const int& a, const int& b)	// swap values of arguments passed by const-reference
//{
//	int temp;
//	temp = a;
//	a = b;
//	b = temp;
//}

int main()	// test swaps
{
	int x = 7;
	int y = 9;

	cout << "Before: x = " << x << ", y = " << y << endl;
	swap_v(x, y);															// replace by call to swap_v, swap_r, or swap_cr
	cout << "After: x = " << x << ", y = " << y << endl;

	cout << "Before: 7 = " << 7 << ", 9 = " << 9 << endl;
	swap_v(7, 9);															// replace by call to swap_v, swap_r, or swap_cr
	cout << "After: 7 = " << 7 << ", 9 = " << 9 << endl << endl;

	const int cx = 7;
	const int cy = 9;

	cout << "Before: cx = " << cx << ", cy = " << cy << endl;
	swap_v(cx, cy);															// replace by call to swap_v, swap_r, or swap_cr
	cout << "After: cx = " << cx << ", cy = " << cy << endl;

	cout << "Before: 7.7 = " << 7.7 << ", 9.9 = " << 9.9 << endl;
	swap_v(7.7, 9.9);														// replace by call to swap_v, swap_r, or swap_cr
	cout << "After: 7.7 = " << 7.7 << ", 9.9 = " << 9.9 << endl << endl;

	double dx = 7.7;
	double dy = 9.9;

	cout << "Before: dx = " << dx << ", dy = " << dy << endl;
	swap_v(dx, dy);															// replace by call to swap_v, swap_r, or swap_cr
	cout << "After: dx = " << dx << ", dy = " << dy << endl;

	cout << "Before: 7.7 = " << 7.7 << ", 9.9 = " << 9.9 << endl;
	swap_v(7.7, 9.9);														// replace by call to swap_v, swap_r, or swap_cr
	cout << "After: 7.7 = " << 7.7 << ", 9.9 = " << 9.9 << endl << endl;
}