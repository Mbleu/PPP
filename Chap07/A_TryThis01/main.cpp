/*Calculator program*/

// Grammar:
// 
// Expression:
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
//      "{" Expression "}"             // grouping
//      "-" Primary
//      "+" Primary
// 
// Number :
//      floating - point - literal

#include "../../std_lib_facilities.h"

//------------------------------------------------------------------------------

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value 
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
    :full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full = false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case ';':    // for "print"
    case 'q':    // for "quit"
    case '{': case '}': case '(': case ')': case '!': case '+': case '-': case '*': case '/':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);         // put digit back into the input stream
        double val;
        cin >> val;              // read a floating-point number
        return Token('8', val);   // let '8' represent "a number"
    }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback() 

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '{':    // handle '{' expression '}'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}') error("'}' expected");
        return d;
    }
    case '(':    // handle '(' expression ')'
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error("')' expected");
        return d;
    }
    case '8':            // we use '8' to represent a number
        return t.value;  // return the number's value
    case '-':
        return -primary();
    case '+':
        return primary();
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------

// deal with !
double secondary()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '!':
        {
            int x = left;
            if (x != left)
                cout << "Warning, truncation necessary to evaluate factorial.\n";
            if (x == 0)
                left = 1;
            else {
                for (int i = x - 1; i > 0; --i) {
                    int xsave = x;
                    x *= i;
                    if (i != 0 && x / i != xsave)   error("Integer overflow during factorial evaluation");
                }
                left = x;
            }
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = secondary();
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '*':
            left *= secondary();
            t = ts.get();
            break;
        case '/':
        {
            double d = secondary();
            if (d == 0) error("divide by zero");
            left /= d;
            t = ts.get();
            break;
        }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while (true) {
        switch (t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

int main()
try
{
    while (cin) {
        cout << "> ";
        Token t = ts.get();
        while (t.kind == ';') t = ts.get();     // eat ';'
        if (t.kind == 'q') {
            keep_window_open();
            return 0;
        }
        ts.putback(t);
        cout << "= " << expression() << '\n';
    }
    keep_window_open();
    return 0;

    //cout << "Welcome to our simple calculator.\nPlease enter expressions using floating-point numbers.\n\n"
    //    << "Calculator: Please enter an expression followed by ';' to have it evaluated. You may use 0-9, ., +, -, *, /, !, () or {}.\n"
    //    << "Enter 'q' to quit.\n";
    //double val = 0;
    //cout << "\n> ";
    //while (cin) {
    //    //cout << "> ";   // print prompt
    //    

    //    Token t = ts.get();

    //    if (t.kind == 'q') break; // 'q' to quit
    //    if (t.kind == ';')        // ';' for "print now"
    //        cout << "= " << val << "\n> ";
    //    else
    //        ts.putback(t);
    //    val = expression();
    //    // cout << "> ";
    //}
    //keep_window_open();
}
catch (exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return 1;
}
catch (...) {
    cerr << "exception \n";
    keep_window_open("~~");
    return 2;
}

//------------------------------------------------------------------------------