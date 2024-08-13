/*Program that takes two files containing sorted whitespace-separated words and merges them, preserving order.
Test files used here are: birds.txt, mammals.txt*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

void merge_sorted_files(ifstream& ifile1, ifstream& ifile2, ofstream& ofile)	// Takes two files containing sorted whitespace-separated words and merges them, preserving order
{
	string word;
	vector<string> words;
	while (ifile1 >> word) words.push_back(word);	// input words from files
	while (ifile2 >> word) words.push_back(word);
	sort(words.begin(), words.end());				// sort the words together

	if (!(ifile1.eof() && ifile2.eof())) throw exception("error: merge_sorted_files(ifstream&, ifstream&, ofstream&): read fail");	// post: must reach EOF on both files
	ifile1.clear(ios_base::eofbit);					// reads successful, remove fail flags leaving only eof flags
	ifile2.clear(ios_base::eofbit);

	for (int i = 0; i < words.size(); ++i) {		// ouput words to file
		ofile << words[i];
		if (i + 1 < words.size()) ofile << endl;	// avoid a newline at the end
	}
}

int main()	// Test merge_sorted_files()
try {
	// Input two file names
	cout << "Please enter the names of the two files you wish to concatenate, separated by 'enter':" << endl
		<< '>';
	string ifilename1;
	cin >> ifilename1;
	ifstream ifs1{ ifilename1 };
	if (!ifs1) throw exception("error: main(): can't open input file");
	cout << '>';
	string ifilename2;
	cin >> ifilename2;
	ifstream ifs2{ ifilename2 };
	if (!ifs2) throw exception("error: main(): can't open input file");

	// Merge the two files
	cout << "Please enter the name of a file to ouput to:" << endl
		<< '>';
	string ofilename;
	cin >> ofilename;
	ofstream ofs{ ofilename };
	if (!ofs) throw exception("error: main(): can't open output file");
	merge_sorted_files(ifs1, ifs2, ofs);
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}