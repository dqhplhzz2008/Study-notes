#include<iostream>
#include<string>
#include<cstring>
#include"bankacc.h"
using namespace std;
Bank::Bank() {
	strcpy(name, "no name");
	name[30] = '\0';
	strcpy(account, "100000");
	account[6] = '\0';
	debt = 0.0;
}
Bank::Bank(const char *co, const char *ac, double db)
{
	strncpy(name, co, 29);
	strncpy(account, ac,6);
	name[30] = '\0';
	account[6] = '\0';
	debt = db;

}
Bank::~Bank() {
	cout << "Your account has been deleted.Thank your for using our service.\n";
}
void Bank::show() const
{
	cout << "Account Name: " << name << endl;
	cout << "Account ID: " << account << endl;
	cout << "Debt: $" << debt << endl;
}
void Bank::deposit(const double money)
{
	debt += money;
	cout << "Your Debt: $" << debt << endl;
	cout << "Thank you for using deposit service.Bye~\n";

}
void Bank::withdrawal(const double money) {
	if (money <= debt)
	{
		debt -= money;
		cout << "Your Debt: $" << debt << endl;
	}
		
	else
		cout << "Error, you do not have enough money.\n";
	cout << "Thank you for using withdrawal service.Bye~\n";

}