#include<iostream>
#include<string>
using namespace std;
int main() {
	string first;
	string last;
	string lj = ", ";
	string name;
	cout << "Enter your first name: ";
	getline(cin,first);
	cout << "Enter your last name: ";
	getline(cin,last);
	name = first + lj;
	name += last;
	cout << "Here's the information in a single string: " << name << endl;
	system("pause");
	return 0;
}