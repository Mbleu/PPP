#include "..\..\std_lib_facilities.h"

bool is_prime(int num)	// determine whether a number is prime
{
	constexpr int first_prime{ 2 };

	for (int i{ first_prime }; i < num; ++i) {
		if (num % i == 0)
			return false;
	}
	return true;
}

vector<int> find_n_primes(int n)	// find the first 'n' primes
{
	constexpr int first_prime{ 2 };
	vector<int> primes{};

	for (int i{ first_prime }; primes.size() < n; ++i) {
		if (is_prime(i))
			primes.push_back(i);
	}
	return primes;
}

int main()
{
	int num{ 0 };
	vector<int> primes{};
	cout << "Enter how many primes you would like to find (followed by 'enter'):\n";
	cin >> num;
	primes = find_n_primes(num);
	for (int p : primes)
		cout << p << ", ";
}