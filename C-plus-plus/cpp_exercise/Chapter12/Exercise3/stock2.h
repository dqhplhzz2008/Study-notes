#ifndef STOCK2_H_
#define STOCK2_H_
#include <string>
#include<iostream>
using std::ostream;
using std::istream;
class Stock
{
private:
	char *company;
	int shares;
	double share_val;
	double total_val;
	void set_tot() { total_val = shares * share_val; }
public:
	Stock();
	Stock(const char *co, int n=0, double pr=0.0);
	~Stock();
	void buy(int num, double price);
	void sell(int num, double price);
	void update(double price);
	const Stock & topval(const Stock & s)const;
	//ÓÑÔªº¯Êý£¬ÖØÔØ<<
	friend ostream & operator<<(ostream & os, const Stock & st);

};
#endif // STOCK1_H_