#include<iostream>
#include"stock2.h"
const int STKS = 4;
int main()
{
	using std::cout;
	using std::endl;
	using std::ios_base;
	Stock stocks[STKS] = {
		Stock("Yushuai",12,20.0),
		Stock("Zhang",200,2.0),
		Stock("Ultraman",130,3.25),
		Stock("Hani Mei",60,6.5)
	};
	cout.precision(2);

	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.setf(ios_base::showpoint);
	cout << "Stock holdings\n";
	int st;
	for (st = 0; st < STKS; st++)
		cout<<stocks[st];
	Stock top = stocks[0];
	for (st = 1; st < STKS; st++)
		top = top.topval(stocks[st]);
	cout << "\nMost valuable holding:\n";
	cout<<top;
	system("pause");
	return 0;
}