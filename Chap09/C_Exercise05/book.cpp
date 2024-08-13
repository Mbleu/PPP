#include "book.h"
#include "date.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Helper functions:
bool is_ISBN(const string& ISBN)	// Check if an ISBN is in the valid form n-n-n-x
{
	if (ISBN.size() != 4) return false;

	vector<int> n_indices{ 0,1,2 };				// locations of digits in an ISBN
	vector<int> x_indices{ 3 };					// locations of letters in an ISBN

	for (int i : n_indices)						// check digit locations contain digits
		if (!isdigit(ISBN[i])) return false;

	for (int i : x_indices)						// check letter locations contain letters
		if (!isalpha(ISBN[i])) return false;

	return true;
}

ostream& operator<<(ostream& os, const Genre& genre)	// Print genre
{
	switch (genre) {
	case Genre::fiction:
		return os << "fiction";
	case Genre::nonfiction:
		return os << "nonfiction";
	case Genre::periodical:
		return os << "periodical";
	case Genre::biography:
		return os << "biography";
	case Genre::children:
		return os << "children";
	default:
		return os << "unknown";
	}
}

ostream& operator<<(ostream& os, const Book& book)	// Print book title, author and ISBN
{
	return os << "Title: " << book.get_title() << endl
		<< "Author: " << book.get_author() << endl
		<< "Genre: " << book.get_genre() << endl
		<< "ISBN: " << book.get_ISBN() << endl;
}

Book::Book(const string& ISBN, const string& title, const string& author, const Date& cr_date, const Genre genre)
	: title(title), author(author), cr_date(cr_date), genre(genre) {
	if (!is_ISBN(ISBN)) throw exception("error: Book(): received invalid ISBN");	// pre: must be a valid ISBN
	this->ISBN = ISBN;
}

bool Book::check_out()	// Returns true/false depending on success
{
	if (checked_out) return false;
	checked_out = true;
	return true;
}

bool Book::check_in()	// Returns true/false depending on success
{
	if (!checked_out) return false;
	checked_out = false;
	return true;
}

bool Book::operator==(const Book& book)const	// Compare ISBN numbers
{
	if (ISBN == book.get_ISBN()) return true;
	return false;
}

bool Book::operator!=(const Book& book)const	// Compare ISBN numbers
{
	if (*this == book) return false;
	return true;
}