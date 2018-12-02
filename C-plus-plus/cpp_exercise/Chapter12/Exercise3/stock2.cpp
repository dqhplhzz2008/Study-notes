#include "stock2.h"
#include<iostream>
#include<cstring>
Stock::Stock() {
	std::cout << "Default constructor called\n";
	company = new char[8];
	std::strcpy(company, "no name");
	company[7] = '\0';
	shares = 0;
	share_val = 0.0;
	total_val = 0.0;
}
Stock::Stock(const char *co, int n, double pr)
{
	std::cout << "Constructor using " << co << " called\n";
	int len = std::strlen(co);
	company = new char[len+1];
	std::strcpy(company, co);
	if (n < 0)
	{
		std::cerr << "Number of shares can't be negative."
			<< company << " shares set to 0.\n";
		shares = 0;
	}
	else
		shares = n;
	share_val = pr;
	set_tot();

}
Stock::~Stock()
{
	delete[] company;
	std::cout << "Bye~" << std::endl;
}
void Stock::buy(int num, double price)
{
	if (num < 0)
	{
		std::cerr << "Number of shares purchased can't be negative."
			<< "Transaction is aborted.\n";
	}
	else
	{
		shares += num;
		share_val = price;
		set_tot();
	}
}

void Stock::sell(int num, double price)
{
	using std::cerr;
	if (num < 0)
	{
		cerr << "Number of shares sold can't be negative."
			<< "Transcation is aborted.\n";
	}
	else if (num>shares)
	{
		cerr << "You can't sell more than you have! Transaction is aborted.\n";
	}
	else
	{
		shares -= num;
		share_val = price;
		set_tot();
	}
}

void Stock::update(double price)
{
	share_val = price;
	set_tot();
}

const Stock & Stock::topval(const Stock &s)const
{
	if (s.total_val > total_val)
		return s;
	else
		return *this;
}

ostream & operator<<(ostream & os, const Stock & st)
{
	os << "Company: " << st.company
		<< " Shares: " << st.shares << std::endl
		<< " Share Price: $" << st.share_val
		<< " Total Worth: $" << st.total_val << std::endl;
	// TODO: 在此处插入 return 语句
	return os;
}
