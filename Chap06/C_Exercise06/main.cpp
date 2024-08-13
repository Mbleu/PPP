// Program to check if a sentence is correct according to the following "English" grammar.
//
//	Sentence:
//		Noun Verb						// e.g., birds fly
//	Article Noun Verb					// e.g., the birds fly
//		Sentence Conjunction Sentence	// e.g., birds fly but fish swim,
//												the birds fly but the fish swim
//	Conjunction :
//		"and"
//		"or"
//		"but"
//	Article :
//		"the"
//  Noun :
//		"birds"
//		"fish"
//		"C++"
//	Verb :
//		"rules"
//		"fly"
//		"swim"

#include "..\..\std_lib_facilities.h"

bool is_verb(string word)									// checks whether its a verb or not
{
	vector<string> verbs{ "rules", "fly", "swim" };

	for (string verb : verbs)
		if (word == verb) return true;
	return false;
}

bool is_noun(string word)									// checks whether its a noun or not
{
	vector<string> nouns{ "birds", "fish", "C++" };

	for (string noun : nouns)
		if (word == noun) return true;
	return false;
}

bool is_article(string word)								// checks whether its a article or not
{
	vector<string> articles{ "the" };

	for (string article : articles)
		if (word == article) return true;
	return false;
}

bool is_conjunction(string word)							// checks whether its a conjunction or not
{
	vector<string> conjunctions{ "and", "or", "but" };

	for (string conjunction : conjunctions)
		if (word == conjunction) return true;
	return false;
}

bool is_sentence(vector<string>& sentence)					// checks whether its a sentence or not
{
	if (sentence.empty()) error("error: is_sentence: empty vector received");	//pre: check for empty vector

	reverse(sentence.begin(), sentence.end());				// reverse the vector, so that pop_back() will apply to the next word in the sentence

	string word = sentence.back();							// get the next word in sentence
	sentence.pop_back();									// delete it from the vector

	if (is_article(word)) {
		if (sentence.empty()) return false;					// ends in an article, not a sentence
		word = sentence.back();								// get the next word in sentence
		sentence.pop_back();
	}
	if (is_noun(word)) {
		if (sentence.empty()) return false;					// ends in an article, not a sentence
		word = sentence.back();								// get the next word in sentence
		sentence.pop_back();

		if (is_verb(word)) {
			if (sentence.empty()) return true;				// ends in a verb, its a sentence
			word = sentence.back();							// get the next word in sentence
			sentence.pop_back();

			if (is_conjunction(word)) {						// conjunction leads on to next sentence
				if (sentence.empty()) return false;			// ends in conjunction, not a sentence
				reverse(sentence.begin(), sentence.end());	// reverse the vector again before passing since sentence() will reverse it again
				if (is_sentence(sentence)) return true;		// ends in another sentence, its a sentence
			}
			return false;									// sentence not followed by conjunction, not a sentence
		}
		return false;										// noun not followed by a verb, not a sentence
	}
	return false;											// doesn't begin with article or noun, not a sentence
}

int main()
try {
	cout << "Please enter a sentence to have it checked for correct grammar. Terminate your sentence with a 'space' followed by a fullstop '.'\n"
		 << "To exit, enter 'e'.\n";

	while (1) {
		vector<string> sentence;
		string input{ "" };
		while (cin >> input && input != ".") {				// loop until input is terminated by a '.' or invalid input, '.' is discarded
			if (input == "e") return 0;						// user exits
			sentence.push_back(input);
		}
		if (cin.fail()) error("error: main: input could not be stored in a string");

		if (is_sentence(sentence))
			cout << "OK\n";
		else
			cout << "not OK\n";
	}

	return 0;
}
catch (exception& e) {
	cerr << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Unknown exception.\n";
	return 2;
}