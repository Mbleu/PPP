// Program for playing an alphabetical variation of "Bulls and Cows", where the player tries to guess the computer's 4 letter code.

#include "..\..\std_lib_facilities.h"

int main()
try {
	cout << "Let's play \"Bulls and Cows\"!\nThe objective of the game is to guess the 4 letter code. All 4 letters are unique.\n"
		<< "A bull is a correct letter in the correct place. A cow is a correct letter in an incorrect place.\n"
		<< "Make guesses in the form: ASDF;\n\n"
		<< "To begin, provide a random number seed in the form an integer.\n";

	char play_again{'y'};															// flag for whether the player wants to play again
	int seed{ 0 };

	if (!(cin >> seed)) error("error: bad seed input");							// get seed from player
	seed_randint(seed);																// seed the random number generator

	while (play_again == 'y') {
		constexpr int code_length{ 4 };
		vector<char> code, guess;

		while (code.size() < code_length) {											// generate random 4 letter code with no repeated letters
			char randchar = (char)randint('A', 'Z');
			for (char c : code)
				if (c == randchar) continue;						
			code.push_back(randchar);
		}

		// pre: guesses must: be upper or lowercase letters from A-Z, be exactly four letters long, have no repeated letters
		// post: guess must match the code
		while (guess != code) {
			int bulls{ 0 }, cows{ 0 };
			guess.clear();

			cout << "Make a guess: ";

			for (char c{ ' ' }; c != ';';) {										// read in guess
				if (!(cin >> c)) error("error: bad guess input");
				guess.push_back(c);
			}
			guess.pop_back();														// discard ';'

			bool invalid_guess{ false };
			for (char ic : guess) {													// check if guess contains only letters
				if ((ic < 'A' || ic > 'Z') && (ic < 'a' || ic > 'z')) {
					invalid_guess = true;
				}
			}
			if (guess.size() != code_length) {										// check number of letters in guess
				invalid_guess = true;
				cout << "Wrong number of letters.\n";
				continue;
			}
			for (int i = 0; i < code_length; ++i) {									// check for repeated letters in guess
				for (int j = i + 1; j < code_length; ++j) {
					if (guess[i] == guess[j]) {
						invalid_guess = true;
					}
				}
			}
			if (invalid_guess) {													// invalid guess, guess again
				cout << "Contains non-letter or repeated letter.\n";
				continue;
			}

			for (char & c : guess)
				c = toupper(c);

			cout << "Guess taken: ";												// clearly ouputs guess taken by computer, in case user used strange format
			for (char c : guess)
				cout << c;
			cout << '\n';

			for (int i = 0; i < code_length; ++i) {									// loops over the letters of the guess
				for (int j = 0; j < code_length; ++j) {								// loops over the letters of the code
					if (guess[i] == code[j]) {										// matching letter found
						if (i == j)													// same place, bull
							++bulls;
						else														// different place, cow
							++cows;
					}
				}
			}
			cout << bulls << " bull(s) and " << cows << " cow(s)\n";
		}

		cout << "Correct!\n" << "Would you like to play again? Enter 'y' or 'n'.\n";
		if (!(cin >> play_again) ) error("error: bad play again input");
	}
}
catch (exception& e) {
	cerr << e.what() << '\n';
}
catch (...) {
	cerr << "error: unkown exception" << '\n';
}