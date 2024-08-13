#pragma once
#include "book.h"
#include "patron.h"
#include "date.h"
#include <vector>

class Library {
public:
	struct Transaction {	// Keeps records of book check outs
		Transaction(const Book& book, const Patron& patron, const Date& date)
			: book(book), patron(patron), date(date) {}
		Book book;
		Patron patron;
		Date date;																// date book is being checked out
	};
	void add_book(const Book& book);				// add a book to the library
	void add_patron(const Patron& patron);			// add a patron to the library
	void check_out(std::string ISBN, int lib_card);	// check out a book for a patron
	void check_in(std::string ISBN, int lib_card);	// check back in a book for a patron
	std::vector<std::string> get_debters() const;	// returns a list of names of all patrons who currently owe fees
	int gen_lib_card() const;						// generate a new unique library card number
	void credit(int lib_card, double amount);		// issue a fee or credit

private:
	std::vector<Book> books;
	std::vector<Patron> patrons;
	std::vector<Transaction> transactions;

	Book& get_book(std::string ISBN);				// find reference to book in library via ISBN
	Patron& get_patron(int lib_card);				// find reference to patron in library via library card number
};