//C++ Primer Plus Edition 5
//Chapter 6 Homework 3
#include<iostream>
#include<cctype>
using namespace std;
void showmenu();
int main() {
	showmenu();
	char choice;
	cin.get(choice);
	while ((choice != 'c') && (choice != 'p') && (choice != 't') && (choice != 'g'))
	{
		cout << "Please enter a c,p,t,g: ";
		//cin.get(choice);
		cin.ignore();
	}
	switch (choice)
	{
	case 'c':
		cout << "This is carnivore's answer.\n";
		break;
	case 'p':
		cout << "This is pianist's answer.\n";
		break;
	case 't':
		cout << "A maple is a tree.\n";
		break;
	case 'g':
		cout << "This is game's answer.\n";
		break;
	default:
		break;
	}
	system("pause");
	return 0;
}

void showmenu() {
	cout << "Please enter one of the following choices.\n"
		"c)carnivore            p)pianist\n"
		"t)tree                 g)game\n";
}