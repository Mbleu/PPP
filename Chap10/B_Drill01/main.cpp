/*Program for reading point coordrinates from the user, outputting to a file and then reading that file.*/

#include <fstream>	// no need for <iostream> as well since <fstream> already includes it for itself
#include <vector>
#include "..\..\std_lib_facilities.h"
using namespace std;

void discard_input()	// discards buffered input up to and including the next newline
{
	cin.clear();
	while (cin.get() != '\n');
}

struct Point {	// x,y coord
	int x;
	int y;
};
// Point Helper Functions:
istream& operator>>(istream& is, Point& p)	// Read input point in form x y
{
	int x, y;
	if (!(is >> x >> y)) return is;

	p.x = x;
	p.y = y;
	return is;
}
ostream& operator<<(ostream& os, const Point& p)	// Output point in form (x,y), this general ostream works for files as well
{
	return os << '(' << p.x << ',' << p.y << ')';
}
ifstream& operator>>(ifstream& ifs, Point& p)	// Read input point from file in form (x,y)
{
	char c1, c2, c3;
	int x, y;

	ifs >> c1 >> x >> c2 >> y >> c3;			// read into variables
	if (!ifs.good()) return ifs;				// stop if full point couldn't be read
	if (c1 != '(' || c2 != ',' || c3 != ')') {	// stop if point is incorrectly formatted
		ifs.clear(ios_base::failbit);
		return ifs;
	}

	p.x = x;
	p.y = y;
	return ifs;
}
bool operator==(const Point& p1, const Point& p2)	// Compare 2 points' x,y coords
{
	return p1.x == p2.x && p1.y == p2.y;
}

int main()
try {
	// Input points from user:
	cout << "Please enter 7 (x,y) pairs with a space between each value, e.g. 10 4 5 6...:" << endl;
	vector<Point> original_points;
	for (int i = 0; i < 7; ++i) {																		// read in up to 7 points
		cout << '>';																					// prompt
		Point p;
		if (!(cin >> p)) {																				// if point invalid, stop reading points
			cout << "Not a valid (x,y) pair, input sequence terminated." << endl;
			discard_input();
			break;
		}
		original_points.push_back(p);
	}

	// Ouput points to user:
	for (Point p : original_points)
		cout << p << endl;

	// Ouput processed points to file:
	cout << "Please enter name of output file: ";									
	string oname;
	cin >> oname;
	ofstream ofs{ oname };																				// (create and) open an ouput file
	if (!ofs) error("can't open output file ", oname);
	for (Point p : original_points)																		// process and output points to file
		ofs << p << endl;
	ofs.close();																						// close the file

	// Input processed points from file:
	ifstream ifs{ oname };																				// open an input file (the ouput file from above)
	if (!ifs) error("can't open input file ", oname);
	vector<Point> processed_points;
	for (Point p; ifs >> p;) {																			// store processed points
		if (ifs.bad()) error("corrupted file ", oname);
		if (ifs.fail()) error("input file text incorrectly formatted ", oname);
		if (ifs.eof()) break;
		processed_points.push_back(p);
	}

	// Output points and processed points to user:
	cout << "Original points:" << endl;
	for (Point p : original_points)
		cout << p << endl;
	cout << "Processed points:" << endl;
	for (Point p : processed_points)
		cout << p << endl;

	// Compare points to processed points:
	if (original_points != processed_points) cout << "Something's wrong!" << endl;
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}