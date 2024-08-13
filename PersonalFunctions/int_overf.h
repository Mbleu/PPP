#pragma once
#include <limits>

int avoid_overf_add(int a, int b);

// Takes two integers and an operation (+, -, *, / and %).
// Checks for overflow without causing one. Overflow will throw error. Otherwise performs operation and returns solution.
int avoid_overf(int a, int b, char op)
{
	constexpr int imin{ std::numeric_limits<int>::min() };													// min integer value
	constexpr int imax{ std::numeric_limits<int>::max() };													// max integer value

	switch (op) {
	case '+':
		return avoid_overf_add(a, b);

	case '-':
		if (b == imin && a >= 0) throw runtime_error("error: avoid_overf: overflow detected");				// special case due to 2's compliment, avoids overflow, imin == -imin so calcs correct
		b = -b;																								// converts into addition
		return avoid_overf_add(a, b);
	
	case '*': {
		int mult{ 0 };
		bool ans_neg{ false };
		if (a < 0 && b < 0) {																				// both negative, result will be pos, make both pos
			if (a == imin || b == imin) throw runtime_error("error: avoid_overf_add: overflow detected");	// special case due to 2's compliment
			a = -a;
			b = -b;
		}
		if (a < 0 && b >= 0) {																				// one pos one neg, result will be neg, make both pos but remember sign
			if (a == imin) throw runtime_error("error: avoid_overf_add: overflow detected");				// special case due to 2's compliment
			ans_neg = true;
			a = -a;
		}
		if (b < 0 && a >= 0) {																				// one pos one neg, result will be neg, make both pos but remember sign
			if (b == imin) throw runtime_error("error: avoid_overf_add: overflow detected");				// special case due to 2's compliment
			ans_neg = true;
			b = -b;
		}
		for (int i = 0; i < a; ++i) {																		// multiply through addition
			mult = avoid_overf_add(mult, b);
		}
		if (ans_neg) {																						// add back the neg sign if needed
			if (mult == imin) throw runtime_error("error: avoid_overf_add: overflow detected");				// special case due to 2's compliment (shouldn't happen here but check is to be sure)
			mult = -mult;
		}
		return mult;
	}
	case'/':
		if (b == 0) throw runtime_error("error: avoid_overf: division by 0");
		if (a == imin && b == -1) throw runtime_error("error: avoid_overf: overflow detected");
		return a / b;

	case '%':
		if (b == 0) throw runtime_error("error: avoid_overf: division by 0");
		if (a == imin && b == -1) throw runtime_error("error: avoid_overf: overflow detected");
		return a % b;

	default:
		throw runtime_error("error: avoid_overf: unknown operation");
		break;
	}
}

// Takes two integers.
// Checks for overflow without causing one. Overflow will throw error. Otherwise performs addition and returns solution.
int avoid_overf_add(int a, int b)
{
	constexpr int imin{ std::numeric_limits<int>::min() };													// min integer value
	constexpr int imax{ std::numeric_limits<int>::max() };													// max integer value

	if ((a >= 0 && b <= 0) || (a <= 0 && b >= 0))															// one positive one negative, no overflow possible
		return a + b;

	if (a > 0 && b > 0) {																					// both positive
		if (imax - a - b < 0) throw runtime_error("error: avoid_overf_add: overflow detected");
		else return a + b;
	}

	if (a < 0 && b < 0) {																					// both negative
		if (a == imin || b == imin) throw runtime_error("error: avoid_overf_add: overflow detected");		// special case due to 2's compliment
		if (imin - a - b > 0) throw runtime_error("error: avoid_overf_add: overflow detected");
		else return a + b;
	}
}