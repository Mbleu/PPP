/*Program for testing use cases for const non-reference parameters.*/

#include <iostream>
using namespace std;

double var = 5;

void foo(const double var_copy)
{
    var += var_copy;
    var += var_copy;
}

int main()
try {
    cout << var << endl;
    foo(var);
    cout << var << endl;
}
catch (...) {
    return 1;
}