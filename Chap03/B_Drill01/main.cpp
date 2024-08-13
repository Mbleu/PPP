#include "..\..\std_lib_facilities.h"

int main()
{
	cout << "Please enter the name of the person you want to write to (followed by 'enter'):\n";
	string recipient_name;
	cin >> recipient_name;

	cout << "Please enter the age of the person you want to write to (followed by 'enter'):\n";
	int recipient_age = 0;
	cin >> recipient_age;

	cout << "Please enter the name of a friend (followed by 'enter'):\n";
	string friend_name;
	cin >> friend_name;

	cout << "Please enter an 'm' if the friend is male and an 'f' is the friend is female (followed by 'enter'):\n";
	char friend_sex = 0;
	cin >> friend_sex;

	cout << "Dear, " << recipient_name << "!\n\n" << "\tHow are you? I am fine. I miss you.\n" << "Have you seen " << friend_name << " recently?\n";
	if (friend_sex == 'm') {
		cout << "If you see " << friend_name << " please ask him to call me.\n";
	}
	if (friend_sex == 'f') {
		cout << "If you see " << friend_name << " please ask her to call me.\n";
	}

	cout << "I hear you just had a birthday and you are " << recipient_age;
	if (abs(recipient_age) == 1) {
		cout << " year old.\n";
	}
	else {
		cout << " years old.\n";
	}
	if (recipient_age <= 0) {
		simple_error("you're kidding!");
	}
	if (recipient_age >= 110) {
		simple_error("you're kidding!");
	}
	if (recipient_age < 12 && recipient_age > 0) {
		cout << "Next year you will be " << recipient_age + 1 << " years old.\n";
	}
	if (recipient_age == 17) {
		cout << "Next year you will be able to drive.\n";
	}
	if (recipient_age > 70) {
		cout << "I hope you are enjoying retirement.\n";
	}

	cout << "Yours sincerely,\n\nWill";

	return 0;
}