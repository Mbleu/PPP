// Program for playing "Bulls and Cows", where the player tries to guess the computer's 4 digit code.

#include "..\..\std_lib_facilities.h"

// Discards all input currently in the buffer and resets cin for new use.
void flush_cin()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Copies the digits of an integer into a vector as separate elements.
// preconditions: must receive a positive integer
vector<int> int_to_vect(int val)
{
	if (val < 0)
		error("error: int_to_vect: non-positive integer received");

	vector<int> digits;
	 do {								// do-while loop ensures that a val with an inital value of 0 will still be copied into the vector
		digits.push_back(val % 10);		// stores the right most digit of val in the vector
		val /= 10;						// shortens val, by removing the right most digit and discarding through truncation
	 } while (val > 0);					// once val has reached 0, it has run out of digits

	return digits;
}

// Checks a vector for a repeated element.
bool repeated_elem(vector<int> v)
{
	for (int i = 0; i < v.size(); ++i) {		// together, the nested loops compare each element of the vector to the others
		for (int j = 0; j < v.size(); ++j) {
			if (i == j)							// skip comparing the same element with itself
				break;
			else if (v[i] == v[j]) {			// matching element found
				return true;
			}
		}
	}

	return false;
}

int main()
try {
	cout << "Let's play \"Bulls and Cows\"!\nThe objective of the game is to guess the 4 digit code. All 4 digits are unique.\n"
		<< "A bull is a correct digit in the correct place. A cow is a correct digit in an incorrect place.\n"
		<< "Leading 0s will be assumed if not provided.\n";

	vector<int> v_code, v_guess;								// vectors to store code and guess as a series of single digits
	int code = 1234, guess = 0;									// variables to store code and guess as whole numbers
	int bulls = 0, cows = 0;

	v_code = int_to_vect(code);									// copy the digits of the code into the vector

	// pre: guesses must: be integers, be positive, be exactly four digits long, have no repeated digits
	// post: guess must match the code
	while (guess != code) {
		bulls = 0, cows = 0;									// reset the bulls and cows at the start of each round
		cout << "Make a guess: ";

		if (!(cin >> guess) || guess < 0 || guess > 9999) {		// enforces guesses: be integers, be positive, be exactly four digits long (including leading 0s)
			flush_cin();
			cout << "Invalid guess.\n";
			continue;											// returns to the start of the game loop
		}

		v_guess = int_to_vect(guess);							// copy the digits of the guess into the vector

		if (guess < 1000)										// adds leading 0s to the vector
			v_guess.push_back(0);
		if (guess < 100)
			v_guess.push_back(0);
		if (guess < 10)
			v_guess.push_back(0);

		cout << "Guess taken: ";
		for (int i = v_guess.size() - 1; i >= 0; --i)			// clearly ouputs the guess taken by the computer, in case the user used strange formatting/leading 0s
			cout << v_guess[i];
		cout << '\n';

		if (repeated_elem(v_guess)) {							// enforces guesses: have no repeated digits)
			flush_cin();
			cout << "Invalid guess. Repeated digit(s).\n";
			continue;											// returns to the start of the game loop
		}

		for (int i = 0; i < 4; ++i) {							// loops over the 4 digits of the guess
			for (int j = 0; j < 4; ++j) {						// loops over the 4 digits of the code
				if (v_guess[i] == v_code[j]) {					// matching digit found
					if (i == j)									// same place, bull
						++bulls;
					else										// different place, cow
						++cows;
				}
			}
		}
		cout << bulls << " bull(s) and " << cows << " cow(s)\n";
	}

	cout << "Correct!\n";
}
catch (exception& e) {
	cerr << e.what();
}