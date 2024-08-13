/*Program for concatenating two files. Test files used here are: hello.txt, world.txt*/

#include <iostream>
#include <fstream>
using namespace std;

void concat_files(ifstream& ifile1, ifstream& ifile2, ofstream& ofile)	// Concatenate two files into a third
{
	string s;
	while (ifile1.peek() != EOF && ifile1.good()) { s += ifile1.get(); }	// keep reading chars from file until the EOF or a read fail
	while (ifile2.peek() != EOF && ifile2.good()) { s += ifile2.get(); }
	if (!ifile1 || !ifile2) throw exception("error: concat_files(ifstream&, ifstream&, ofstream&): read fail");	// post
	ofile << s;
}

int main()	// Test concat_files()
try {
	// Input two file names
	cout << "Please enter the names of the two files you wish to concatenate, separated by 'enter':" << endl
		<< '>';
	string filename1;
	cin >> filename1;
	ifstream ifs1{ filename1 };
	if (!ifs1) throw exception("error: main(): can't open input file");
	cout << '>';
	string filename2;
	cin >> filename2;
	ifstream ifs2{ filename2 };
	if (!ifs2) throw exception("error: main(): can't open input file");

	// Concatenante files and ouput to new file
	ofstream ofs{ filename1 + '+' + filename2};	// concatenate the file names too
	concat_files(ifs1, ifs2, ofs);
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}