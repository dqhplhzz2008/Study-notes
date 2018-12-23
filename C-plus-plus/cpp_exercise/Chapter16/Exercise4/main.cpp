//C++ Primer Plus(5th Edition)
//Chapter 16 Exercise 4
//Designed by Yushuai Zhang
#include<iostream>
#include<set>
using namespace std;
const int SIZE = 8;
int reduce(long ar[], int n);
int main()
{
	long exm[SIZE]
		= { 2,5,4,1,2,8,7,3 };
	int an;
	an = reduce(exm, SIZE);
	cout << "The number is " << an << endl;
	system("pause");
	return 0;
}
int reduce(long ar[], int n)
{
	set<long> set_num;
	for (int i = 0; i < n; i++)
		set_num.insert(ar[i]);
	int num;
	num = set_num.size();
	return num;
}
