//C++ Primer Plus Edition 5
//Chapter 8 Homework 6
#include<iostream>
using namespace std;
template<typename T>
T maxn(T *a, const int n);
template<> const char* maxn(const char **a, const int n);

int main()
{
	int a[6] = {3,6,1,8,2,9 };
	double b[4] = { 9.8,8.56,193.1,4.3 };
	const char *c[5] = { "HAHAHA", "BALABALA", "XIAOMOXIAN", "hengli", "very good" };
	cout << maxn(a, 6) << endl;
	cout << maxn(b, 4) << endl;
	cout << maxn(c, 5) << endl;
	system("pause");
	return 0;
}

template<typename T>
T maxn(T *a, const int n)
{
	for (int i = 0; i < n; i++)
		if (a[i] > a[0]) a[0] = a[i];
	return a[0];
}

template<> const char* maxn(const char **a, const int n)
{
	int i, j = 0;
	for (i = 0; i<n; i++)
		if (strlen(a[i])>strlen(a[j])) j = i;
	return a[j];

}


