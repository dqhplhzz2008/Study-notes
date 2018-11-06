//C++ Primer Plus Edition 5
//Chapter 6 Homework 1
#include<iostream>
#include<cctype>
using namespace std;
int main() {
	cout << "Enter text for analysis and type @"
		"to terminate input.\n";
	char ch;
	cin.get(ch);
	while (ch != '@') {
		if (!isdigit(ch))
		{
			if (islower(ch))
				ch = toupper(ch);
			else if (isupper(ch))
				ch = tolower(ch);
			cout << ch;

		}
		cin.get(ch);
	}

	system("pause");
	return 0;
}
//错误代码，判断如果是数字执行continue的话就会循环判断字符是不是等于@，第一个字符就无限循环。
//else同样。
//while (ch != '@') {
//	if (isdigit(ch))
//		continue;
//	else if (isalpha(ch))
//	{
//		cout << ch << endl;
//		if (islower(ch))
//			ch = toupper(ch);
//		else if (isupper(ch))
//			ch = tolower(ch);
//		cout << ch;
//	}
//	else
//		continue;
//}