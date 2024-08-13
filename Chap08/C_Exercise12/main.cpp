/*Program that prints all the elements of a vector up to a first or second occurrence of a string.*/

#include <vector>
#include <iostream>
using namespace std;

void print_until_s(const vector<string>& v, string quit)    // Print a vector up to (but not including) the first occurrence of a given string
{
    if (v.size() == 0) throw exception("error: print_until_s: received empty vector");  // pre: vector must not be empty

    for (string s : v) {
        if (s == quit) return;
        cout << s << '\n';
    }
}

void print_until_ss(const vector<string>& v, string quit)    // Print a vector up to (but not including) the second occurrence of a given string
{
    if (v.size() == 0) throw exception("error: print_until_ss: received empty vector");  // pre: vector must not be empty

    bool second_quit{ false };

    for (string s : v) {
        if (s == quit) {
            if (!second_quit) second_quit = true;
            else return;
        }
        cout << s << '\n';
    }
}

int main()
try {
    // Test Cases:
    //vector<string> v{};                                                                                 // empty vector
    //vector<string> v{"hello", "I", "am", "a", "computer"};                                              // vector with no occurrences of the quit string
    //vector<string> v{ "hello", "quit", "I", "quit", "am", "quit", "a", "quit", "computer", "quit" };    // vector with many occurrences of the quit string
    vector<string> v{"1 sdg 34\n", "/n\n\n 3525  jdg aiouh", "quit", "..2"};                            // vector with varied strings
    string quit = "quit";

    print_until_s(v, quit);
    print_until_ss(v, quit);
}
catch (exception& e) {
    cerr << e.what() << endl;
    return 1;
}
catch (...) {
    return 2;
}