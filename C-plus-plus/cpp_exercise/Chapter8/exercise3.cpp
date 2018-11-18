//C++ Primer Plus Edition 5
//Chapter 8 Homework 3
#include<iostream>
#include<string>
#include<cctype>
using namespace std;

string convert_Big(string &str);
int main() {
	string text,up;
	cout << "Enter a string (q to quit):" << endl;
	getline(cin, text);
	while (text != "q" && text!="Q")
	{
		cout << convert_Big(text) << endl;
		cout << "Next string (q to quit): " << endl;
		getline(cin, text);

	}
	system("pause");
	return 0;
}
//string可以被看做是字符数组
string convert_Big(string & str)
{
	int limit = str.size();
	for (int i = 0; i < limit; i++)
	{
		if(isalpha(str[i]))
			str[i] = toupper(str[i]);
	}
	return str;
}

