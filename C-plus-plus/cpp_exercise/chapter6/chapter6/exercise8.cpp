//C++ Primer Plus Edition 5
//Chapter 6 Homework 8
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
const int MAXSIZE = 50;
int main() {
	char filename[MAXSIZE];
	ifstream inFile;
	cout << "Please enter the file's name: ";
	cin.getline(filename, MAXSIZE);
	inFile.open(filename);
	if (!inFile.is_open()) {
		cout << "Open this file error."<<endl;
		exit(EXIT_FAILURE);
	}
	char ch;
	int count = 0;
	inFile >> ch;
	while (inFile.good()) {
		++count;
		inFile >> ch;
	}
	if (inFile.eof()) {
		cout << "Have reached end of this file.\n";
	}
	else if (inFile.fail()) {
		cout << "Input terminated by data mismatch.\n";
	}
	else
		cout << "unknown reason to stop.\n";
	if (count == 0) {
		cout << "No data in this file.\n";
	}
	else {
		cout << "There are " << count << " characters in this file.\n";
	}
	inFile.close();
	system("pause");
	return 0;
}