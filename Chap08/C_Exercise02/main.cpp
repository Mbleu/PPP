#include <vector>
#include <iostream>
using namespace std;

bool check_of(int a, int b)	// checks for int sum overflow
{
	long long big{ (long long)a + (long long)b };
	int small = big;
	if (big != (long long)small) return true;
	return false;
}

void print(string vname, const vector<int>& v)	// prints out a vector
{
	cout << vname << " = { ";
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i];
		if (i == v.size() - 1) break;
		cout << ", ";
	}
	cout << " }" << endl;
}

void fibonacci(int x, int y, vector<int>& v, int n)	// creates a fibonacci sequence. x = first element, y = second element, v = empty vector, n = number of elements
{
	if (v.size() != 0) throw exception("error: fibonacci(): received non-empty vector");			// pre: vector must be empty
	if (n <= 0) throw exception("error: fibonacci(): received non-positive number of elements");	// pre: number of elements must be positive

	v.push_back(x);
	v.push_back(y);
	for (int i = 2; i < n; ++i) {																	// continue from the third element
		if (check_of(v[i - 1], v[i - 2])) {
			cout << "Approx max integer: " << abs(v[i - 1]) << endl;
			break;
		}
		v.push_back(v[i - 1] + v[i - 2]);
	}
}

vector<int> reverse_cr(const vector<int>& v)	// create a new reversed vector
{
	vector<int> vr;

	for (int i = v.size() - 1; i >= 0; --i) {
		vr.push_back(v[i]);
	}

	return vr;
}

void reverse_r(vector<int>& v)	// reverse the existsing vector
{
	for (int i = 0; i < v.size() / 2; ++i) {	// swaps pairs of elements starting with the lowest and the highest
		int temp{ v[i] };
		v[i] = v[v.size() - 1 - i];
		v[v.size() - 1 - i] = temp;
	}
}

int main()
try {
	vector<int> v;
	fibonacci(1, -10, v, 11);	// test vector

	print("myfib", v);

	print("myfib_rev_cr", reverse_cr(v));

	reverse_r(v);
	print("myfib_rev_r", v);
}
catch (exception& e) {
	cerr << e.what() << endl;
	return 1;
}
catch (...) {
	return 2;
}