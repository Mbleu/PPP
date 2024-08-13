#include "..\..\std_lib_facilities.h"

int area(int length, int width)		// calculate area of a rectangle
{
	if (length <= 0 || width <= 0) return -1;
	return length * width;
}

int framed_area(int x, int y)		// calculate area within frame
{
	constexpr int frame_thickness{ 2 };
	return area(x - frame_thickness, y - frame_thickness);
}

int main()
{
	int x = 4;
	int y = 4;
	int z = 4;
	//...
	int area1 = area(x, y);
	if (area1 <= 0) error("non-positive area\n");
	int area2 = framed_area(4, z);
	if (area2 <= 0) error("non-positive area\n");
	int area3 = framed_area(y, z);
	if (area3 <= 0) error("non-positive area\n");
	double ratio = double(area1) / area3;				// convert to double to get floating-point division

	cout << "area1: " << area1 << "\narea2: " << area2 << "\narea3: " << area3 << "\nratio: " << ratio;

	// i've detected all the errors here because i've put after every function call to area
}