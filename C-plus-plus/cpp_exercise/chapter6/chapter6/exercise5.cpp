//C++ Primer Plus Edition 5
//Chapter 6 Homework 5
#include<iostream>
const double level1 = 0.1;
const double level2 = 0.15;
const double level3 = 0.2;
using namespace std;
int main() {
	double tvarp;
	double cus;
	cout << "Please input your money: ";
	cin >> tvarp;
	while (cin.good() && (tvarp > 0))
	{
		if (tvarp <= 5000)
			cus = 0.0;
		else if (tvarp > 5000 && tvarp <= 15000)
			cus = (tvarp - 5000)*level1;
		else if (tvarp > 15000 && tvarp <= 35000)
			cus = 10000 * level1 + (tvarp - 15000)*level2;
		else if (tvarp > 35000)
			cus = 10000 * level1 + 20000 * level2 + (tvarp - 35000)*level3;
		cout << "您需要交税" << cus << " tvarp.\n";
		cout << "Please input your money: ";
		cin >> tvarp;
	}
	cout << "Bye\n";

	system("pause");
	return 0;
}