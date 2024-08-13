#pragma once
#include "date.h"
#include <string>
#include <iostream>

enum class Genre {
	fiction, nonfiction, periodical, biography, children
};

class Book {
public:
	Book(const std::string& ISBN, const std::string& title,
		const std::string& author, const Date& cr_date, const Genre genre);
	std::string get_ISBN()const { return ISBN; }
	std::string get_title()const { return title; }
	std::string get_author()const { return author; }
	Date get_cr_date()const { return cr_date; }
	Genre get_genre()const { return genre; }
	bool is_checked_out()const { return checked_out; }
	bool check_out();														// returns true/false depending on success
	bool check_in();														// returns true/false depending on success
	bool operator==(const Book& book)const;									// compare ISBN numbers
	bool operator!=(const Book& book)const;									// compare ISBN numbers

private:
	std::string ISBN;
	std::string title;
	std::string author;
	Date cr_date;															// copyright date
	Genre genre;
	bool checked_out{ false };
};

// Helper function:
bool is_ISBN(const std::string& ISBN);	// check if an ISBN is in the valid form n-n-n-x
std::ostream& operator<<(std::ostream& os, const Genre& genre);	// print genre
std::ostream& operator<<(std::ostream& os, const Book& book);	// print book title, author and ISBN