#include "library.h"
#include "book.h"
#include "patron.h"
#include "date.h"
using namespace std;

void Library::add_book(const Book& book)	// Add a book to the library
{
	for (Book b : books)																						// pre
		if (book == b) throw exception("error: Library::add_book(const Book&): library already has this book");

	books.push_back(book);
}	

void Library::add_patron(const Patron& patron)	// Add a patron to the library
{
	patrons.push_back(patron);
}

void Library::check_out(string ISBN, int lib_card)	// Check out a book for a patron
{
	Book& book{ get_book(ISBN) };																							// pre: library must have the book
	if (book.is_checked_out()) throw exception("error: Library::check_out(std::string, int): book already checked out");	// pre
	Patron& patron{ get_patron(lib_card) };																					// pre: must be patron of the library
	if (is_debt(patron)) throw exception("error: Library::check_out(std::string, int): patron owes fees");					// pre

	book.check_out();																										// mark book as checked out
	transactions.push_back(Transaction(book, patron, Date(2023, Month::jun, 14)));											// *for now just a constant date*
}

void Library::check_in(string ISBN, int lib_card)	// Check back in a book for a patron
{
	Book& book{ get_book(ISBN) };																							// pre: library must have the book
	if (!book.is_checked_out()) throw exception("error: Library::check_in(std::string, int): book not checked out");		// pre
	Patron& patron{ get_patron(lib_card) };																					// pre: must be patron of the library

	book.check_in();																										// mark book as checked in
}

Book& Library::get_book(std::string ISBN)	// Find a book in library via ISBN, returns reference to original for modifying
{
	if (!is_ISBN(ISBN)) throw exception("error: Library::get_book(std::string): invalid ISBN");	// pre

	for (Book& b : books)
		if (ISBN == b.get_ISBN()) { return b; }
	throw exception("error: Library::get_book(std::string): book not found");
}

Patron& Library::get_patron(int lib_card)	// Find a patron in library via library card number, returns reference to original for modifying
{
	for (Patron& p : patrons)
		if (lib_card == p.get_lib_card()) { return p; }
	throw exception("error: Library::get_patron(int): patron not found");
}

vector<string> Library::get_debters() const	// Returns a list of names of all patrons who currently owe fees
{
	vector<string> debters;
	for (const Patron& patron : patrons)
		if (is_debt(patron)) debters.push_back(patron.get_name());

	return debters;
}

int Library::gen_lib_card() const	// Generate a new unique library card number
{
	return patrons.size();
}

void Library::credit(int lib_card, double amount)	// Issue a fee or credit
{
	Patron& patron{ get_patron(lib_card) };	// pre: must be patron of the library

	patron.set_balance(amount);	// alter balance by the amount
}