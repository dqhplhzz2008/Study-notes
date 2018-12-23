//C++ Primer Plus(5th Edition)
//Chapter 16 Exercise 1
//Designed by YushuaiZhang
#include<iostream>
#include<string>
using namespace std;
bool is_hui(const string & st);
int main()
{
	string input;
	cout << "Enter words(q to quit):\n";
	while (cin >> input && input != "q")
	{
		if (is_hui(input))
			cout << "True\n";
		else
			cout << "False\n";

		cout << "Enter another words(q to quit):\n";
	}
	cout << "Done!\n";
	system("pause");
	return 0;
}

bool is_hui(const string & st)
{
	int size = st.size();
	if (size % 2 == 0)
	{
		for (int i = 0; i < (size / 2); i++)
			if (st[i] != st[size - 1 - i])
				return false;
	}
	else if (size % 2 == 1)
	{
		for (int i = 0; i <= (size / 2); i++)
			if (st[i] != st[size - 1 - i])
				return false;
	}
	return true;
}