#include "..\..\std_lib_facilities.h"

int main()
{
	vector<string> names;
	string temp_name{ "" };
	vector<int> scores;
	int temp_score{ 0 };
	string s_search{ "" };
	int i_search{ 0 };

	cout << "Enter a set of name-and-value pairs each separated by spaces, e.g. Joe 17 Barbara 22 James 23 (followed by 'enter').\nTo terminate input, enter: \"NoName 0\".\n";

	for (bool input_ter{ false }; !input_ter;) {
		if (!(cin >> temp_name) || !(cin >> temp_score))
			input_ter = true;
		if (temp_name == "NoName" && temp_score == 0)
			input_ter = true;

		for (string s : names) {
			if (temp_name == s) {
				cerr << "Error: Name already entered.\n";
				input_ter = true;
			}
		}

		if (!input_ter) {
			names.push_back(temp_name);
			scores.push_back(temp_score);
		}
	}

	for (int i{ 0 }; i < names.size(); ++i) {
		cout << names[i] << ' ' << scores[i] << '\n';
	}

	cout << "Enter a name to search for that person's score or enter a score to search for anyone with that score (followed by 'enter').\n";
	cout << "To exit the program, type \"exit\" (followed by 'enter').\n";
	for (bool input_term{ false }; !input_term;) {
		if (cin >> i_search) {
			cout << "List of people who scored " << i_search << ":\n";
			vector<int> indices;
			for (int i{ 0 }; i < scores.size(); ++i) {
				if (i_search == scores[i])
					indices.push_back(i);
			}
			if (indices.size() == 0)
				cout << "Score not found.\n";
			else
				for (int i : indices)
					cout << names[i] << " \n";
		}
		else {
			cin.clear();
			if (cin >> s_search) {
				if (s_search == "exit")
					break;
				cout << s_search << " scored :\n";
				int index{ -1 };
				for (int i{ 0 }; i < names.size(); ++i) {
					if (s_search == names[i]) {
						index = i;
						break;
					}
				}
				if (index == -1)
					cout << "Name not found.\n";
				else
					cout << scores[index] << " \n";
			}
			else
				break;
		}
	}
}