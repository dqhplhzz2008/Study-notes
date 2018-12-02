
#include "person.h"
using namespace std;
const int ARRSIZE = 5;
int main()
{
	Person* person[ARRSIZE];
	int ct = 0;
	for (ct = 0; ct < ARRSIZE; ct++) {
		int choice;
		cout << "Enter the person category:\n"
			<< "1: person 2:gunslinger"
			<< "3: pokerplayer 4: BadDude 0:quit\n";
		cin >> choice;
		while (choice < 0 || choice > 4) {
			cout << "Please enter 1, 2, 3, 4 or 0: ";
			cin >> choice;
		}
		if (choice == 0) {
			break;
		}
		cin.get();
		switch (choice) {
		case 1:
			person[ct] = new Person;
			break;
		case 2:
			person[ct] = new Gunslinger;
			break;
		case 3:
			person[ct] = new PokerPlayer;
			break;
		case 4:
			person[ct] = new BadDude;
			break;
		}
		person[ct]->set();
	}

	cout << "\nAll Person\n";
	for (int i = 0; i < ct; ++i) {
		cout << endl;
		person[i]->show();
	}
	for (int i = 0; i < ct; ++i) {
		delete person[i];
	}
	system("pause");
	cout << "Bye.\n";
	return 0;
}
