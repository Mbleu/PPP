//#include "..\..\std_lib_facilities.h"		// this was causing an issue with creating vector<bool>
#include <vector>
#include <iostream>
using namespace std;

// implementation of the sieve of Eratosthenes way of finding primes
// pass it a max value and it will return a vector of bools marking each number as prime or not
vector<bool> sieve(int max)
{					
	if (max <= 0) {
		cerr << "Invalid value for max: " << max << "\nFunction will now exit.\n";
		exit(1);
	}

	constexpr int first_prime{ 2 };
	vector<bool> primes{};					// bools used here to be space efficient. the bool flags the value as prime or not but its location in the vector acts as the actual value
	for (int i{0}; i <= max; ++i)			// creates a vector of as many elements as there are numbers up to max
		primes.push_back(true);				// all candidates start off flagged as prime numbers

	for (int i{ 0 }; i < first_prime; ++i)	// sets 0 and 1 (if the vector is big enough) to not prime
		primes[i] = false;

	for (int i{ first_prime }; i < primes.size(); ++i) {	// starting with the first prime number (2), goes through every element of the vector
		if (primes[i]) {									// skip over any already marked not prime
			for (int j{ 2 }; i * j < primes.size(); ++j)	// go through multiples of the current element, marking them as not prime. start at 2 to not mark the current element as not prime
				primes[i * j] = false;
		}
	}

	return primes;
}

int main()
{
	int max{ 0 };
	vector<bool> primes{};
	cout << "Enter a positive integer to find all the prime numbers up to it (followed by 'enter'):\n";
	if (!(cin >> max))
		exit(1);
	primes = sieve(max);
	for (int i{ 0 }; i < primes.size(); ++i) {
		if (primes[i])
			cout << i << ", ";
	}
}