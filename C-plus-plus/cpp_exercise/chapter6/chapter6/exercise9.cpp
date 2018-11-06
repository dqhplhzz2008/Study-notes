//C++ Primer Plus Edition 5
//Chapter 6 Homework 9
#include<iostream>
#include<cctype>
#include<string>
#include<fstream>
using namespace std;
const int MAXSIZE = 50;
struct donation
{
	string name;
	double money;

};
int main() {
	char filename[MAXSIZE];
	ifstream inFile;
	cout << "Please enter the file's name: ";
	cin.getline(filename, MAXSIZE);
	inFile.open(filename);
	if (!inFile.is_open()) {
		cout << "Open this file error." << endl;
		exit(EXIT_FAILURE);
	}
	int num;
	int count = 0;
	inFile >> num;
	inFile.get();//³Ôµô»»ÐÐ·û
	donation *donaer = new donation[num];
	for (int i = 0; i < num; i++)
	{
		getline(inFile, donaer[i].name);
		inFile >> donaer[i].money;
		inFile.get();//³Ôµô»»ÐÐ·û
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
	inFile.close();
	system("pause");
	return 0;
}