#include<iostream>
#include<string>
using namespace std;
int main() {
	string name;
	string dessert;

	cout << "Enter your name: \n";
	getline(cin, name);//利用string输入带空格的一行的时候，要用getline这种方式进行。
	//cin是参数，指出到哪里去查号输入。
	cout << "Enter your favorite dessert: \n";
	getline(cin, dessert);
	cout << "I have some delicious " << dessert;
	cout << " for you, " << name << ".\n";
	system("pause");
	return 0;
}