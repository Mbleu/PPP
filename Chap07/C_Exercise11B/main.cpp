/*
	This is a rewrite of Exercise 13-14 from Chapter 4 to include rules learnt in Chapter 7.
	Last updated 26/04/23 by William Falcon-Uff
	This program finds prime numbers up to a max value using the sieve of Eratosthenes.
*/

#include <vector>
#include <iostream>
using namespace std;

vector<bool> sieve(int max)	// Marks numbers as prime or not up to a given max value. Returns a boolean vector where the indices act as the numbers.
{
	constexpr int first_prime = 2;
	if (max < first_prime) throw runtime_error("error: sieve: received invalid max value");	// pre

	vector<bool> primes(max + 1, true);														// boolean vector where indices act as numbers, all numbers initially marked prime

	primes[0] = false;																		// marks 0 and 1 as not prime
	primes[1] = false;

	for (int num = 0; num <= max; ++num)													// check each number up to max
		if (primes[num])																	// skip if already marked not prime
			for (int mult = 2 * num; mult <= max; mult += num)								// mark all multiples of the prime as not prime
				primes[mult] = false;

	return primes;
}

vector<int> find_primes(int max)	// Finds primes up to a given max value.
{
	vector<bool> marked_nums = sieve(max);				// create a list of numbers marked as prime or not
	vector<int> primes;

	for (int num = 0; num <= max; ++num)				// extract just the prime numbers from the marked list
		if (marked_nums[num]) primes.push_back(num);

	return primes;
}

void clear_is()	// Discards input up to and including the next newline.
{
	while (cin.get() != '\n');
	return;
}

int main()
try {
	cout << "Enter a positive integer to find all the prime numbers up to it (followed by 'enter'):\n";

	while (1) try {																						// loop to allow input re-entry in case of bad input
		cout << "> ";																					// prompt user

		int max = 0;
		if (!(cin >> max) || cin.peek() != '\n') throw runtime_error("error: main: invalid input max");

		vector<int>primes = find_primes(max);

		cout << "Primes = {";
		for (int prime : primes) {																		// print the primes
			if (prime != primes.back())
				cout << prime << ", ";
			else cout << prime << "}\n";
		}
			
		return 0;
	}
	catch (runtime_error& e) {																			// handles errors related to erroneous input
		cerr << e.what() << endl;
		cin.clear();
		clear_is();
	}
}
catch (...) {																							// handles fatal exceptions
	cerr << "exception\n";
	return 1;
}