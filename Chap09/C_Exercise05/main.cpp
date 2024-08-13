/*Program that could be plausible software for a library, with a book class, borrowing, etc.*/
#include "book.h"
#include "date.h"
#include "patron.h"
#include "library.h"
using namespace std;

int main()	// Testing functionality
try {
	Library library;

	// Adding books
	Book book0("115x", "Twilight", "Stephenie Meyer", Date(2005, Month::oct, 5), Genre::fiction);
	library.add_book(book0);
	Book book1("116x", "Life and Death: Twilight Reimagined", "Stephenie Meyer", Date(2015, Month::oct, 6), Genre::fiction);
	library.add_book(book1);

	// Book operations
	cout << "Book info:" << endl << book0 << endl << book1 << endl;
	if (book0 == book1) cout << "true" << endl << endl;
	if (book0 != book1) cout << "false" << endl << endl;

	// Adding patrons
	Patron patron0("Peter Jamesson", library.gen_lib_card());
	library.add_patron(patron0);
	Patron patron1("Peter Peterson", library.gen_lib_card());
	library.add_patron(patron1);
	Patron patron2("James Jefferson", library.gen_lib_card());
	library.add_patron(patron2);

	// Patron operations
	cout << "Patron info:" << endl << patron0 << endl << patron1 << endl << patron2 << endl;

	// Crediting patrons
	library.credit(0, 5.46);	// correct patron, positive amount
	//library.credit(-1, 5.46);	// incorrect patron
	//library.credit(0, -5.46);	// correct patron, negative amount
	library.credit(1, -1);		// correct patron, negative amount
	library.credit(2, -5.46);	// correct patron, negative amount (second to test the list below)

	// Print a list of names of all patrons who owe fees
	cout << "Patrons with outstanding fees:" << endl;
	for (string name : library.get_debters())
		cout << name << endl;
	cout << endl;

	// Checking books out/in
	library.check_out("116x", 0);		// valid/correct ISBN, valid patron
	//library.check_out("117x", 0);		// valid/incorrect ISBN, valid patron
	//library.check_out("11xx", 0);		// invalid ISBN, valid patron
	//library.check_out("116x", -1);	// valid/correct ISBN, invalid patron

	library.check_in("116x", 0);	// valid/correct ISBN, valid patron
	//library.check_in("117x", 0);	// valid/incorrect ISBN, valid patron
	//library.check_in("11xx", 0);	// invalid ISBN, valid patron
	//library.check_in("116x", -1);	// valid/correct ISBN, invalid patron
}
catch (InvalidDate) {					// known fatal exception
	cerr << "Invalid date." << endl;
	return 1;
}
catch (exception& e) {					// known fatal exceptions
	cerr << e.what() << endl;
	return 1;
}
catch (...) {							// unknown fatal exceptions
	return 2;
}
