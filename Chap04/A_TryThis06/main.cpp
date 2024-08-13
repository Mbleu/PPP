#include "..\..\std_lib_facilities.h"

// Checks if a given vector of strings contains a given string and returns true or false
bool does_vect_contain(vector<string> v, string s)
{
	for (string temp : v)
		if (s == temp)
			return 1;
	return 0;
}

int main()
{
	vector<string> disliked = { "William", "hello"};

	// Creates a list of words from user input
	cout << "Please enter some words separated by spaces (followed by 'ctrl+z'):\n";
	vector<string> words;
	for (string temp; cin >> temp; )
		words.push_back(temp);
	
	// Outputs a list of words, bleeping out any that are disliked
	for (string temp : words)						
		if (does_vect_contain(disliked, temp)) {
			// Outputs the same number of '*' as there are characters in the word
			for (int i = 0; i < temp.size(); ++i)
				cout << '*';
			cout << ' ';
		}
		else
			cout << temp << ' ';
}