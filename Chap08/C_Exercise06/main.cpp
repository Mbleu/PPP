#include <vector>
#include <iostream>
using namespace std;

void print(string vname, const vector<string>& v)	// prints out a vector
{
	cout << vname << " = { ";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i == v.size() - 1) break;
		cout << ", ";
	}
	cout << " }" << endl;
}

vector<string> reverse_cr(const vector<string>& v)	// create a new reversed vector
{
	vector<string> vr;

	for (int i = v.size() - 1; i >= 0; --i) {
		vr.push_back(v[i]);
	}

	return vr;
}

void reverse_r(vector<string>& v)	// reverse the existsing vector
{
	for (int i = 0; i < v.size() / 2; ++i) {	// swaps pairs of elements starting with the lowest and the highest
		string temp{ v[i] };
		v[i] = v[v.size() - 1 - i];
		v[v.size() - 1 - i] = temp;
	}
}

int main()
try {
	vector<string> v{"hi", "hello", "lol", "m"};	// test vector

	print("myvec", v);

	print("myvec_rev_cr", reverse_cr(v));

	reverse_r(v);
	print("myvec_rev_r", v);
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	return 2;
}