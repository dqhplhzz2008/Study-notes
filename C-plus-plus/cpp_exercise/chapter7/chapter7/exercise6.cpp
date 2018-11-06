//C++ Primer Plus Edition 5
//Chapter 7 Homework 6
#include<iostream>
int fill_array(double ar[], int limit);
void show_array(double ar[], int size);
void reverse_array(double ar[], int size);
using namespace std;
const int MAXSIZE = 20;
int main()
{
	int n;
	double shuzu[MAXSIZE];
	int size = fill_array(shuzu, MAXSIZE);
	show_array(shuzu, size);
	reverse_array(shuzu, size);
	cout << "反转结果：" << endl;
	show_array(shuzu, size);
	system("pause");
	return 0;
}
int fill_array(double ar[], int limit)
{
	double temp;
	int i;
	for (i = 0; i<limit; i++)
	{
		cout << "Enter value#" << (i + 1) << " \n";
		cin >> temp;
		if (!cin)
		{
			cin.clear();
			cout << "bad input:\n";
			break;
		}
		else
			ar[i] = temp;
	}
	return i;
}
void show_array(double ar[], int size)
{
	for (int i = 0; i<size; i++)
		cout << "Value #" << (i + 1) << ": " << ar[i] << endl;;
}
void reverse_array(double ar[], int size)
{
	int i, j;
	for (i = 1, j = size - i - 1; i<j; i++, j--)
	{
		double temp = ar[i];
		ar[i] = ar[j];
		ar[j] = temp;
	}
}