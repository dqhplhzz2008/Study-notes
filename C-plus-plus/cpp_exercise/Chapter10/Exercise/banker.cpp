#include<iostream>
#include<string>
#include<cstring>
#include"bankacc.h"
using namespace std;

int main() {
	cout << "This is Bank example 1:" << endl;
	Bank banks1;
	banks1.show();
	cout << "After depositing..."<<endl;
	double depos1 = 3692.21;
	banks1.deposit(depos1);
	cout << "After withdrawal..." << endl;
	banks1.withdrawal(1252.63);
	cout << "#########################################" << endl;
	double money2 = 8945.32;
	Bank banks2 = Bank("Yushuai Zhang", "H6365", money2);
	banks2.show();
	cout << "After depositing..." << endl;
	double depos2 = 235.21;
	banks2.deposit(depos2);
	cout << "After withdrawal..." << endl;
	banks2.withdrawal(625.63);

	system("pause");
	return 0;
}