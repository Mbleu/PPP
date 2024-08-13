/*Program that determines information about a vector of strings and prints it.*/

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> countvs(const vector<string>& vs)   // Returns the number of letters of each string in the given vector
{
    if (vs.size() == 0) throw exception("error: print_until_s: received empty vector");  // pre: vector must not be empty

    vector<int> vi;
    for (string s : vs)
        vi.push_back(s.size());

    return vi;
}

string longvs(const vector<string>& vs)   // Returns the longest string in the given vector
{
    if (vs.size() == 0) throw exception("error: print_until_s: received empty vector");  // pre: vector must not be empty

    string longest = vs[0];
    for (string s : vs)
        if (s.size() > longest.size()) longest = s;

    return longest;
}

string shortvs(const vector<string>& vs)   // Returns the shortest string in the given vector
{
    if (vs.size() == 0) throw exception("error: print_until_s: received empty vector");  // pre: vector must not be empty

    string shortest = vs[0];
    for (string s : vs)
        if (s.size() < shortest.size()) shortest = s;

    return shortest;
}

int main()
try {
    vector<string> vs{"hello", "I", "am", "a", "computer"};                                                         // example vector
    vector<int> vi = countvs(vs);
    string longest = longvs(vs);
    string shortest = shortvs(vs);

    sort(vs.begin(), vs.end());                                                                                     // sort will put all capitals ahead of lowercase
    string lexi_first = vs[0];
    string lexi_last = vs[vs.size() - 1];

    for (int i : vi)
        cout << i << ", ";
    cout << endl << "Longest: " << longest << endl << "Shortest: " << shortest << endl
        << "Lexicographically first: " << lexi_first << endl << "Lexicographically last: " << lexi_last << endl;
}
catch (exception& e) {
    cerr << e.what() << endl;
    return 1;
}
catch (...) {
    return 2;
}