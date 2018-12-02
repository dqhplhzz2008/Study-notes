//C++ Primer Plus Edition 5
//Chapter 6 Homework 6
#include<iostream>
#include<cctype>
#include<string>
using namespace std;
struct donation
{
	string name;
	double money;

};
int main() {
	int num;
	int count = 0;
	cout << "Please input the number of donationer: ";
	cin >> num;
	cin.get();//³Ôµô»»ÐÐ·û
	donation *donaer = new donation[num];
	for (int i = 0; i < num; i++)
	{
		cout << "Enter the name: ";
		getline(cin, donaer[i].name);
		cout << "Enter money: ";
		cin >> donaer[i].money;
		cin.get();//³Ôµô»»ÐÐ·û
	}
	cout << "****************************" << endl;
	cout << "Grand Patrons" << endl;
	cout << "****************************" << endl;
	for (int i = 0; i < num; i++) {
		if (donaer[i].money > 10000) {
			++count;
			cout << "Name: " << donaer[i].name << endl;
			cout << "Donate Money: " << donaer[i].money << endl;
			cout << endl;
		}
	}
	if (count == 0)
	{
		cout << "None" << endl;
	}
	count = 0;
	cout << "****************************" << endl;
	cout << "Patrons" << endl;
	cout << "****************************" << endl;
	for (int i = 0; i < num; i++) {
		if (donaer[i].money <= 10000) {
			++count;
			cout << "Name: " << donaer[i].name << endl;
			cout << "Donate Money: " << donaer[i].money << endl;
			cout << endl;
		}
	}
	if (count == 0)
	{
		cout << "None" << endl;
	}
	delete[] donaer;
	system("pause");
	return 0;
}