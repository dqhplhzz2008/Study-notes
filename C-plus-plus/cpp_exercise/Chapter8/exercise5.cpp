//C++ Primer Plus Edition 5
//Chapter 8 Homework 5
#include<iostream>
using namespace std;
template<typename T>
T max5(T *a);
int main() {
	int inte[5] = { 23, 55, 65, 12, 34 };
	int max_int = max5(inte);
	double dou[5] = { 12.3,14.3,11.9,89.6,1.8 };
	double max_dou = max5(dou);
	cout << "Integer MAX= " << max_int << endl;
	cout << "Double MAX= " << max_dou << endl;
	system("pause");
	return 0;
}

template<typename T>
T max5(T *a)
{
	T temp = a[0];
	for (int i = 1; i < 5; i++)
	{
		if (a[i] < temp)
			temp = a[i];
	}
	return temp;
}