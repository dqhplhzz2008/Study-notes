//C++ Primer Plus(5th Edition)
//Chapter 16 Exercise 5
//Designed by Yushuai Zhang
#include<iostream>
#include<set>
using namespace std;
const int SIZE = 8;
template<class T>
int reduce(T ar[], int n);
int main()
{
	long exm[SIZE]
		= { 2,5,4,1,2,8,7,3 };
	int an;
	an = reduce(exm, SIZE);
	cout << "The number of exm is " << an << endl;
	string exs[SIZE] = { "Hello","Message","David","Cheung","Hello","David","Haha","No one" };
	int ans;
	ans = reduce(exs, SIZE);
	cout << "The number of exs is " << ans << endl;
	system("pause");
	return 0;
}

template<class T>
int reduce(T ar[], int n)
{
	set<T> set_num;
	for (int i = 0; i < n; i++)
		set_num.insert(ar[i]);
	int num;
	num = set_num.size();
	return num;
}
