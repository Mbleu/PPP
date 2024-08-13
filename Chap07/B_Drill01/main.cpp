
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

// Bugs Fixed: -Missing Token(type, name) constructor
//				
//				-Missing return d; inside primary() for case '('
// *Not a bug?* -Missing case '+' inside primary() for evaluating positive unary
//				-In default case of Token_stream::get(), inside the while loop was s=ch; instead of s+=ch;
//				-In default case of Token_stream::get(), if the string is "quit" the Token was constructed with type name instead of type quit
//				-In set_value() the for loop had i <= names.size() instead of just i < names.size()
//				-Missing case '%' inside term() for evaluating moduli
// 
// Improvements: -Replace the 'a' inside declaration() to its symbolic constant name
// 
//
// Grammar:
// 
// Calculation :
//		Statement
//		Print
//		Quit
//		Calculation Statement
// 
// Statement :
//		Declaration
//		Expression
// 
// Declaration :
//		"#" Name "=" Expression
// 
// Expression :
//      Term
//      Expression "+" Term         // addition
//      Expression "–" Term         // subtraction
// 
// Term :
//      Secondary
//      Term "*" Secondary             // multiplication
//      Term "/" Secondary              // division
//      Term "%" Secondary               // remainder (modulo)
// 
// Secondary :
//      Primary
//      Primary "!"                 // factorial
// 
// Primary :
//      Number
//      "(" Expression ")"             // grouping
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

	void ignore(char);									// ignores all characters from the raw text input up to and including a given character
};

const char let = 'L';		// symbolic constants, the value of which is fairly meaningless but allows for the use of the constant name
const char quit = 'Q';
const char root2 = 'R';		// called root2 because its the squareroot
const char power = 'P';
const char print = ';';
const char number = '8';
const char name = 'a';

Token Token_stream::get()	// gets and returns the next Token, first checks the buffer otherwise creates one. It handles raw text.
{
	if (full) { full = false; return buffer; }								// if full, returns token already in buffer rather than creating new one
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':																// these literals represent themselves as the Token types
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
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
	{	cin.unget();														// its a number, so unget() the first digit and create a Token of the whole number
	double val;
	cin >> val;
	return Token(number, val);
	}
	case '#':
		return Token(let);
	default:
		if (isalpha(ch)) {													// variable names must start with a letter
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;	// variable names can contain letters or numbers
			cin.unget();													// put back the last char from the raw input text that wasn't part of the variable name
			if (s == "exit") return Token(quit);
			if (s == "sqrt") {
				if (cin.get(ch) && ch == '(') return Token(root2);
				error("Bad token");
			}
			if (s == "pow") {
				if (cin.get(ch) && ch == '(') return Token(power);
				error("Bad token");
			}
			return Token(name, s);											// create Token of type name and with a name of s
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)	// ignores all characters from the raw text input up to and including a given character
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {	// holds a created variable's name and value such as PI, 3.14159
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)	// searches for a variable by name and returns its value
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ", s);
}

void set_value(string s, double d)	// searches for a variable by name and sets its value
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ", s);
}

bool is_declared(string s)	// checks whether a variable already exists or not
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

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
		return get_value(t.name);
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
	return pow(i1,i2);
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
		case '*':								// evaluate term*primary
			left *= primary();
			break;
		case '/':								// evaluate term/primary
		{	double d = primary();
		if (d == 0) error("divide by zero");
		left /= d;
		break;
		}
		case '%':								// evaluate term%primary
		{	int i1 = narrow_cast<int>(left);	// enforce integers
		int i2 = narrow_cast<int>(primary());
		if (i2 == 0) error("%: divide by zero");
		left = i1 % i2;
		break;
		}
		default:								// no more * or / found, return complete evaluated term
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

double declaration()	// creates a variable
{
	Token t = ts.get();													// create variable from the next token
	if (t.kind != name) error("name expected in declaration");			// check that the token is indeed of type name (of a variable)
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");				// check it doesn't already exist
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", name);	// check theres an = after the name
	double d = expression();											// evaluate any expression that may have been input as its value
	names.push_back(Variable(name, d));
	return d;
}

double statement()	// performs declarations and expressions
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()	// discards input up to the next print symbol (used after there has been bad input)
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()	// calculator that prompts the user to input and ouputs a solution
{
	names.push_back(Variable("k", 1000));		// predefined constants

	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();	// skip print symbols
		if (t.kind == quit) return;				// user quits
		ts.unget(t);
		cout << result << statement() << endl;	// action the statement
	}
	catch (runtime_error& e) {					// handles errors related to erroneous input, won't handle bug related errors
		cerr << e.what() << endl;
		clean_up_mess();
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