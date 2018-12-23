//C++ Primer Plus(5th Edition)
//Chapter 17 Exercise 1
//Designed by Yushuai Zhang
#include<iostream>
using namespace std;
int main()
{
	cout << "Please enter some words.\n";
	char ch;
	int count=0;
	while (cin.peek() != '$')
	{
		cin.get(ch);
		count++;
	}
	cout << "The number of this word is " << count << "." << endl;
	system("pause");
	return 0;
}