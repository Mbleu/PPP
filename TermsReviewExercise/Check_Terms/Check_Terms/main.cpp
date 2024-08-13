/*Program for finding and removing previously defined terms from the list at the end of a chapter.*/

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main()
{
	// Store full list of terms a vector
	ifstream ifs{ "terms_checklist.txt" };
	vector<string> terms;
	while (ifs.good()) {							// read until eof
		char c;
		string term;
		while (ifs.get(c) && c != '\n')				// read until end of term
			term += c;
		terms.push_back(term);
	}
	ifs.close();

	// Store list of terms to add in a vector
	ifs.open("terms_toadd.txt");
	vector<string> toadd;
	while (ifs.good()) {							// read until eof
		char c;
		string term;
		while (ifs.get(c) && c != '\n')				// read until end of term
			term += c;
		toadd.push_back(term);
	}
	ifs.close();

	// Erase duplicates
	vector<string> deleted;
	for (string& s1 : toadd)
		for (const string& s2 : terms)
			if (s1 == s2) {
				deleted.push_back(s1);
				s1.erase();
				break;
			}

	// Ouput duplicates
	cout << "Duplicate words erased:" << endl;
	for (const string& s : deleted)
		cout << s << endl;

	// Save amended list of terms to add
	ofstream ofs{ "terms_toadd.txt" };
	for (const string& s : toadd)
		ofs << s << endl;
}