/*Program that prompts user to enter ages for a series of names, sorts the name-age pairs and then prints them.
* It then repeats for a second list and tests whether the lists are identical.*/

#include <string>
#include <vector>
#include <iostream>
using namespace std;

void clear_is()	// Discards input up to and including the next newline.
{
	while (cin.get() != '\n');
}

class Name_pairs {
public:
	void read_names(const vector<string>& inames);				// reads in a list of names and stores them
	const vector<string>& get_names() const { return names; }
	const vector<double>& get_ages() const { return ages; }
	bool operator==(const Name_pairs& np);						// checks if the left-hand (calling instance of Name_pairs) is equal to the right-hand one
	bool operator!=(const Name_pairs& np);						// checks if the left-hand (calling instance of Name_pairs) is not equal to the right-hand one

private:
	vector<string> names;
	vector<double> ages;

	void read_age(const string iname);							// prompts user to enter an age for a name
	string capitalise(string name);								// appropriately capitalise a name
	void sort();												// reorganizes the name-age pairs into alphabetical order by name
	void swap(int i1, int i2);									// swaps the position of two name-age pairs 
};

void Name_pairs::read_names(const vector<string>& inames)	// Reads in a list of names and stores them
{
	for (string s : inames) {
		s = capitalise(s);		// capitalising helps with sorting
		names.push_back(s);
		read_age(s);
	}
	sort();
}

string Name_pairs::capitalise(string name)	// Appropriately capitalise a name
{
	bool capitalise_next{ true };										// first letter always capital
	for (int i = 0; i < name.size(); ++i) {
		if (capitalise_next) name[i] = toupper(name[i]);
		capitalise_next = false;
		if (name[i] == ' ' || name[i] == '-') capitalise_next = true;	// capital after ' ' and '-'
	}
	return name;
}

void Name_pairs::read_age(const string iname)	// Prompts user to enter an age for a name
{
	cout << "Age of " << iname << ":" << endl;

	double iage{ 0 };

	while (1) try {																	// loop until a valid age is entered
		cout << "> ";
		if (!(cin >> iage) || cin.peek() != '\n' || iage < 0) throw exception();	// invalid age input
		ages.push_back(iage);
		break;
	}
	catch (exception) {																// handle bad input to allow for re-entry
		cerr << "Bad input." << endl;
		cin.clear();
		clear_is();
	}
}

void Name_pairs::sort()	// Reorganizes the name-age pairs into alphabetical order by name
{
	if (names.size() != ages.size()) throw exception("error: sort(): unequal number of names and ages");	// pre

	for (int i = 1; i < names.size(); ++i) {																// find the first name out of order
		if (names[i] < names[i - 1]) {
			for (int j = 0; j < names.size(); ++j) {														// find its correct position
				if (names[i] < names[j])
					swap(i, j);																				// note: performs a lot of swaps, might be better with an insert() and erase() (or a move()?)
			}
		}
	}
}

void Name_pairs::swap(int i1, int i2)	// Swaps the position of two name-age pairs 
{
	if (i1 >= names.size() || i2 >= names.size()) throw exception("error: swap(): received index out of range");	// pre
	if (names.size() != ages.size()) throw exception("error: swap(): unequal number of names and ages");			// pre

	string temp_name;
	double temp_age;
	temp_name = names[i1];																							// swaps names
	names[i1] = names[i2];
	names[i2] = temp_name;

	temp_age = ages[i1];																							// swaps ages
	ages[i1] = ages[i2];
	ages[i2] = temp_age;
}

bool Name_pairs::operator==(const Name_pairs& np)	// Checks if the left-hand (calling instance of Name_pairs) is equal to the right-hand one
{
	if (get_names() == np.get_names() && get_ages() == np.get_ages()) return true;
	return false;
}

bool Name_pairs::operator!=(const Name_pairs& np)	// Checks if the left-hand (calling instance of Name_pairs) is not equal to the right-hand one
{
	if (*this == np) return false;
	return true;
}

ostream& operator<<(ostream& os, const Name_pairs& np)
{
	const vector<string>& names{ np.get_names() };					// save references to vectors for cleaner code below
	const vector<double>& ages{ np.get_ages() };

	for (int i = 0; i < names.size(); ++i)
		os << "(" << names[i] << ", " << ages[i] << ")" << endl;

	return os;
}

int main()
try {
	vector<string> names{ "will falcon-uff", "Sally shipton", "james peterson", "james patterson" };
	Name_pairs name_pairs;
	name_pairs.read_names(names);
	cout << name_pairs << endl;

	Name_pairs name_pairs2;																				// operator overload test
	name_pairs2.read_names(names);
	cout << name_pairs2 << endl;
	if (name_pairs == name_pairs2) cout << "Lists of name-pairs are the same." << endl;
	if (name_pairs != name_pairs2) cout << "Lists of name-pairs are not the same." << endl;
}
catch (exception& e) {					// known fatal errors
	cerr << e.what() << endl;
	return 1;
}
catch (...) {							// unknown fatal errors
	cerr << "error: unknown" << endl;
	return 2;
}