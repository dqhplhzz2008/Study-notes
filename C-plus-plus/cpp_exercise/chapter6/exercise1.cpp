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
//������룬�ж����������ִ��continue�Ļ��ͻ�ѭ���ж��ַ��ǲ��ǵ���@����һ���ַ�������ѭ����
//elseͬ����
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