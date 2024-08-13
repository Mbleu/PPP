// Calculator Program
// Last changed 26/04/23 - William Falcon-Uff
// Type help whilst using the calculator for a rundown of its capabilities and how to use them
//
// Grammar:
// 
// Calculation :
//		"\n"						// end of sequence
//		Statement
//		Print
//		Help
//		Quit
//		Calculation Statement		// sequences of calculations
//		Calculation Print
// 		Calculation Help
// 		Calculation Quit
//		Calculation "\n"
// 
// Statement :
//		Declaration
//		Assignment
//		Expression
// 
// Declaration :
//		let Name "=" Expression
//		perm Name "=" Expression
// 
// Assignment :
//		assign Name "=" Expression
// 
// Expression :
//      Term
//      Expression "+" Term         // addition
//      Expression "–" Term         // subtraction
// 
// Term :
//      Primary
//      Term "*" Primary             // multiplication
//      Term "/" Primary             // division
//      Term "%" Primary             // remainder (modulo)
// 
// Primary :
//      Number
//      "(" Expression ")"            // grouping
//      "-" Primary
//      "+" Primary
//		Name
//		"sqrt(" Expression ")"
//		"pow(" Expression "," Expression ")"
// 
// Name :
//		Number
// 
// Number :
//      floating - point - literal

#include "../../std_lib_facilities.h"

struct Token {	// a Token represents a discrete unit of input text (e.g. a number, a '*' sign, a name, a keyword, ...)
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }							// Token(type) for tokenising opertators etc.
	Token(char ch, double val) :kind(ch), value(val) { }			// Token(type, value) for tokenising numbers etc.
	Token(char ch, string name) :kind(ch), name(name), value(0) { }	// Token(type, name) for tokenising variables such as PI etc.
};

class Token_stream {	// handles the creation and handing out of Tokens
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();										// gets and returns the next Token, first checks the buffer otherwise creates one. It handles raw text.
	void unget(Token t) { buffer = t; full = true; }	// "puts back" a token allowing other functions to peek the Token without discarding it

	void ignore(vector<char> stops);					// discards raw text input up to and including the first of a given set of characters
};

const char let = 'L';		// symbolic constants, the value of which is fairly meaningless but allows for the use of the constant name
const char perm = 'P';
const char assign = 'A';
const char help = 'H';
const char quit = 'Q';
const char root2 = 'r';		// called root2 because its the squareroot
const char power = 'p';
const char print = ';';
const char number = '8';
const char name = 'a';

Token Token_stream::get()	// gets and returns the next Token, first checks the buffer otherwise creates one. It handles raw text.
{
	if (full) { full = false; return buffer; }											// if full, returns token already in buffer rather than creating new one
	char ch;
	do {																				// discard all whitespace apart from newline
		cin.get(ch);
	} while (isspace(ch) && ch != '\n');
	switch (ch) {
	case '\n':
	case ';':
	case '(':																			// these literals represent themselves as the Token types
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
	case ',':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.unget();																	// its a number, so unget() the first digit and create a Token of the whole number
	double val;
	cin >> val;
	return Token(number, val);
	}
	default:
		if (isalpha(ch) || ch == '_') {													// variable names must start with a letter or underscore
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;	// variable names can contain letters, numbers and underscores
			cin.unget();																// put back the last char from the raw input text that wasn't part of the variable name
			if (s == "quit") return Token(quit);
			if (s == "Help" || s == "help") return Token(help);
			if (s == "let") return Token(let);
			if (s == "perm") return Token(perm);
			if (s == "assign") return Token(assign);
			if (s == "sqrt") {
				if (cin.get(ch) && ch == '(') return Token(root2);
				error("Bad token");
			}
			if (s == "pow") {
				if (cin.get(ch) && ch == '(') return Token(power);
				error("Bad token");
			}
			return Token(name, s);														// create Token of type name and with a name of s
		}
		error("Bad token");
	}
}

void Token_stream::ignore(vector<char> stops)	// discards raw text input up to but not including the first of a given set of characters
{
	if (full)
		for (char stop : stops)
			if (stop == buffer.kind) return;
	full = false;

	char ch;
	while (cin.get(ch)) {
		for (char stop : stops)
			if (stop == ch) {
				cin.unget();
				return;
			}
	}
}

struct Variable {	// holds a created variable's name and value such as PI, 3.14159
	string name;
	double value;
	bool is_const;
	Variable(string n, double v, bool b) :name(n), value(v), is_const(b) { }
};

class Symbol_table {	// deals with named variables
public:
	double get(string s);
	void set(string s, double d);
	bool is_declared(string s);
	double declaration();
	double assignment();
private:
	vector<Variable> var_table;
};

double Symbol_table::get(string s)	// searches for a variable by name and returns its value
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return var_table[i].value;
	error("get: undefined name ", s);
}

void Symbol_table::set(string s, double d)	// searches for a variable by name and sets its value if its not a constant
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) {
			if (!var_table[i].is_const) {
				var_table[i].value = d;
				return;
			}
			error("set: cannot change a permanent value");
		}
	error("set: undefined name ", s);
}

bool Symbol_table::is_declared(string s)	// checks whether a variable already exists or not
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s) return true;
	return false;
}

Token_stream ts;

Symbol_table symbol_table;

double expression();

double primary()	// evaluates primaries: (expression), unaries, numbers, and variables
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') error("')' expected");
	return d;
	}
	case '+':
		return primary();
	case '-':
		return -primary();
	case number:
		return t.value;
	case name:
		return symbol_table.get(t.name);
	case root2:
	{	double d = expression();
	if (d < 0) error("negative numbers have no real roots");
	t = ts.get();
	if (t.kind != ')') error("')' expected");
	return sqrt(d);
	}
	case power:
	{	double d1 = expression();
	int i1 = narrow_cast<int>(d1);								// enfore integers
	t = ts.get();
	if (t.kind != ',') error("',' expected");
	double d2 = expression();
	int i2 = narrow_cast<int>(d2);
	t = ts.get();
	if (t.kind != ')') error("')' expected");
	return pow(i1, i2);
	}
	default:
		error("primary expected");
	}
}

double term()	// evaluates terms: primary, term*primary, term/primary
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':									// evaluate term*primary
			left *= primary();
			break;
		case '/':									// evaluate term/primary
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%':									// evaluate term%primary
		{	int i1 = narrow_cast<int>(left);		// enforce integers
		int i2 = narrow_cast<int>(primary());
		if (i2 == 0) error("%: divide by zero");
		left = i1 % i2;
		break;
		}
		default:									// no more * or / found, return complete evaluated term
			ts.unget(t);
			return left;
		}
	}
}

double expression()	// evaluates an expression: term, expression + term, expression - term
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':			// evaluate expression + term
			left += term();
			break;
		case '-':			// evaluate expression - term
			left -= term();
			break;
		default:			// no more + or - found, return complete evaluated term
			ts.unget(t);
			return left;
		}
	}
}

double Symbol_table::declaration()	// creates a variable
{
	Token t = ts.get();													// create variable from the next token
	bool is_const = false;
	switch (t.kind) {
	case let:
		is_const = false;
		break;
	case perm:
		is_const = true;
		break;
	default:
		error("keyword expected in declaration");
	}
	t = ts.get();
	if (t.kind != name) error("name expected in declaration");			// check that the token is indeed of type name (of a variable)
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");				// check it doesn't already exist
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);	// check theres an = after the name
	double d = expression();											// evaluate any expression that may have been input as its value
	var_table.push_back(Variable(name, d, is_const));
	return d;
}

double Symbol_table::assignment()	// changes the value of a variable
{
	Token t = ts.get();													// assign to variable from the next token
	if (t.kind != name) error("name expected in assignment");			// check that the token is indeed of type name (of a variable)
	string name = t.name;
	if (!is_declared(name)) error(name, " not declared");				// check it exists
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in assignment of ", name);		// check theres an = after the name
	double d = expression();											// evaluate any expression that may have been input as its value
	set(name, d);
	return d;
}

double statement()	// performs declarations, assignments and expressions
{
	Token t = ts.get();
	switch (t.kind) {
	case let: case perm:
		ts.unget(t);						// don't discard the keyword, declaration() will need it
		return symbol_table.declaration();
	case assign:
		return symbol_table.assignment();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()	// discards input up to the next print or newline (used after there has been bad input)
{
	vector<char> stops{ print, '\n' };
	ts.ignore(stops);
}

void print_help()	// displays instructions for using the calculator
{
	cout << "An expression can contain: numbers(integers and decimals), operators and variables.\n"
		<< "An operator can be: + - * / % () pow(a,b) sqrt()\n"
		<< "pow(a,b) will raise a to the power b. sqrt() will give the square root.\n"
		<< "To declare a variable, use the 'let' keyword and provide a name and value. e.g. let pi = 3.14\n"
		<< "To declare a constant, use the 'perm' keyword instead.\n"
		<< "To change the value of a variable, use the 'assign' keyword instead.\n"
		<< "To print the answer, use either or print command ';' or press 'enter'.\n"
		<< "Type 'quit' to exit.\n";
	return;
}

const string prompt = "> ";
const string result = "= ";

void calculate()	// calculator that prompts the user to input and ouputs a solution
{
	while (true) {
		cout << prompt;
		bool seq_end = false;
		while (!seq_end) try {
			Token t = ts.get();
			switch (t.kind) {
			case '\n':									// end of sequence of entries
				seq_end = true;
				break;
			case print:
				break;
			case help:
				print_help();
				break;
			case quit:
				return;
			default:
				ts.unget(t);
				cout << result << statement() << endl;	// action the statement
				break;
			}
		}
		catch (runtime_error& e) {						// handles errors related to erroneous input, won't handle bug related errors
			cerr << e.what() << endl;
			clean_up_mess();
		}
	}	
}

int main()
try {
	calculate();
	return 0;
}
catch (exception& e) {							// handles bug related errors noticed by a check
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {									// handles bug related errors not noticed by this program
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}