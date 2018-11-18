//C++ Primer Plus Edition 5
//Chapter 8 Homework 7
#include<iostream>
using namespace std;
template<typename T>
T ShowArray(T arr[], int n);

template<typename T>
T ShowArray(T * arr[], int n);
struct debts {
	char name[50];
	double amount;
};
int main(void) {
	int things[6] = { 13,31,103,301,310,130 };
	struct debts mr_E[3] =
	{
		{ "Ima Wolfe",2400.0 },
		{ "Ura Foxe",1300.0 },
		{ "Iby Stout",1800.0 }
	};
	double *pd[3];
	for (int i = 0; i < 3; i++)
		pd[i] = &mr_E[i].amount;
	cout << "Listing Mr.E's counts of things:";
	int ans_int = ShowArray(things, 6);
	cout << ans_int << endl;
	cout << "Listing Mr.E's  debts:";
	double ans_dou= ShowArray(pd, 3);
	cout << ans_dou << endl;
	system("pause");
	return 0;
}

template<typename T>

T ShowArray(T arr[], int n) {
	T ans = arr[0];
	cout << "Template A\n";
	for (int i = 1; i < n; i++)
		ans+=arr[i];
	return ans;
}

template<typename T>
T ShowArray(T*arr[], int n)
{
	T ans=*arr[0];
	cout << "Template B\n";
	for (int i = 1; i < n; i++)
		ans += *arr[i];
	return ans;
}