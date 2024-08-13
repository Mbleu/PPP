// Program that takes in name-score pairs and then allows the user to search by name or score for matching pairs

#include "..\..\std_lib_facilities.h"

struct Name_value {															// stores name score pairs
	string name{ "" };
	int score{ 0 };
};

int main()
{
	vector<Name_value> people;												// store the name score pairs

	cout << "Enter a set of name-and-value pairs each separated by spaces, e.g. Joe 17 Barbara 22 James 23 (followed by 'enter').\nTo terminate input, enter: \"NoName 0\".\n";

	for (bool input_ter{ false }; !input_ter;) {							// loop until input is terminated
		Name_value input_pair;												// temporary storage for input name score pair

		if (!(cin >> input_pair.name) || !(cin >> input_pair.score))		// terminate input if a valid name and score pair are not input
			break;
		if (input_pair.name == "NoName" && input_pair.score == 0)			// terminate input when user enter the "NoName 0" pair
			break;

		for (Name_value person : people) {									// terminate input if the name already exists
			if (input_pair.name == person.name) {
				cerr << "Error: Name already entered.\n";
				input_ter = true;
			}
		}

		if (!input_ter)														// if input hasn't been terminated, add the name score pair to the list
			people.push_back(input_pair);
	}

	for (int i{ 0 }; i < people.size(); ++i) {								// ouput all the name score pairs
		cout << people[i].name << ' ' << people[i].score << '\n';
	}

	cout << "Enter a name to search for that person's score or enter a score to search for anyone with that score (followed by 'enter').\n";
	cout << "To exit the program, type \"exit\" (followed by 'enter').\n";

	for (bool input_term{ false }; !input_term;) {							// loop until input is terminated

		Name_value search;													// stores a searched name or score

		if (cin >> search.score) {											// search by score
			cout << "List of people who scored " << search.score << ":\n";
			int matches{ 0 };												// number of matches found
			for (Name_value person : people) {								// find all matching scores
				if (search.score == person.score) {
					++matches;
					cout << person.name << '\n';							// output names with matching scores
				}
			}
			if (matches == 0)												// no matching score found
				cout << "Score not found.\n";
		}
		else {
			cin.clear();
			if (cin >> search.name) {										// search by name
				if (search.name == "exit")									// terminate input if user exits
					break;
				cout << search.name << " scored :\n";
				bool match{ false };										// has a match been found
				for (Name_value person : people) {							// find all matching names
					if (search.name == person.name) {
						match = true;
						cout << person.score << '\n';						// output score with matching name
						break;
					}
				}
				if (!match)													// no matching name found
					cout << "Name not found.\n";
			}
			else															// no name or score entered, terminate input
				break;
		}
	}
}