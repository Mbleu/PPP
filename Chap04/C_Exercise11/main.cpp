#include "..\..\std_lib_facilities.h"

bool is_prime(int num)	// determine whether a number is prime
{
	constexpr int first_prime{ 2 };

	for (int i{first_prime}; i < num; ++i) {
		if (num % i == 0)
			return false;
	}
	return true;
}

vector<int> find_primes(int max)	// find all the prime numbers up to an upper bound
{
	constexpr int first_prime{ 2 };
	vector<int> primes{};

	for (int i{ first_prime }; i <= max; ++i) {
		if (is_prime(i))
			primes.push_back(i);
	}
	return primes;
}

int main()
{
	int num{ 0 };
	vector<int> primes{};
	cout << "Enter a number to find all the prime numbers smaller than it (followed by 'enter'):\n";
	cin >> num;
	primes = find_primes(num);
	for (int x : primes)
		cout << x << ", ";
}