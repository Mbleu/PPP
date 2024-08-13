#include "..\..\std_lib_facilities.h"

int main()
{
	vector<char> comp_gos{ 'p','s','p','s','s','s','s','r','s','s','p','p','p','s','p','p','p','r','r','s','p','p','s','r','s','s','p','r','p','s','s','s' };
	char player_go{ ' ' };
	int seed{ 0 };
	cout << "Welcome to rock, paper, scissors.\nPlease enter a positive integer to seed the game.\n";

	if (cin >> seed && seed >= 0) {
		cout << "Please enter 'r', 'p' or 's' to play a round.\n";
		for (int i = seed % comp_gos.size(); cin >> player_go; ++i) {
			switch (player_go) {
			case 'r':
				if (comp_gos[i] == 'r')
					cout << "Computer: Rock!\nRound tied.\n";
				else if (comp_gos[i] == 'p')
					cout << "Computer: Paper!\nComputer wins.\n";
				else if (comp_gos[i] == 's')
					cout << "Computer: Scissors!\nYou win.\n";
				break;
			case 'p':
				if (comp_gos[i] == 'r')
					cout << "Computer: Rock!\nYou win.\n";
				else if (comp_gos[i] == 'p')
					cout << "Computer: Paper!\nRound tied.\n";
				else if (comp_gos[i] == 's')
					cout << "Computer: Scissors!\nComputer wins.\n";
				break;
			case's':
				if (comp_gos[i] == 'r')
					cout << "Computer: Rock!\nComputer wins.\n";
				else if (comp_gos[i] == 'p')
					cout << "Computer: Paper!\nYou win.\n";
				else if (comp_gos[i] == 's')
					cout << "Computer: Scissors!\nRound tied.\n";
				break;
			default:
				cout << "Not a valid go.\n";
				break;
			}
		}
	}
}