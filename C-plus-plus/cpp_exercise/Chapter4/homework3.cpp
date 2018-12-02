#include<iostream>
#include<cstring>
using namespace std;
int main() {
	char first[20];
	char last[20];
	cout << "Enter your first name: ";
	cin.getline(first, 20);
	cout << "Enter your last name: ";
	cin.getline(last, 20);
	cout << "Here's the information in a single string: " << last << ", " << first << endl;
	system("pause");
	return 0;
}