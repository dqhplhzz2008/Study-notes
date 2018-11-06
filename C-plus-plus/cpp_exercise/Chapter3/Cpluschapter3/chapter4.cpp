#include <stdio.h>
#include <iostream>
using namespace std;
int main() {
	struct inflatable
	{
		char name[20];
		float volume;
		double price;
	};
	inflatable *ps = new inflatable;
	cout << "Enter name of inflatable item:" << endl;
	cin.get(ps->name,20);
	cout << "Enter volume in cubic feet:" << endl;
	cin >> (*ps).volume;
	cout << "Enter price:$";
	cin >> ps->price;
	cout << "Name: " << (*ps).name << endl;
	cout << "Volume: " << ps->volume << " cubic feet" << endl;
	cout << "Price: $" << ps->price << endl;
	delete ps;
	system("pause");
	return 0;
}