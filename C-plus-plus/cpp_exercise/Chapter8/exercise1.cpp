//C++ Primer Plus Edition 5
//Chapter 8 Homework 1
#include<iostream>
using namespace std;
void show_ch(char *str, int n = 0);
int num = 0;
int main()
{
	char name[10] = "zhang";
	cout << "����ڶ�������Ϊ0����ô��������ǵ�һ�ε��ã���" << endl;
	show_ch(name);
	cout << "�������" << endl;
	cout << "�ڶ��ε�����������" << endl;
	show_ch(name, 3);
	cout << "�����ε�����������" << endl;
	show_ch(name, 9);
	cout << "���Ĵε�����������" << endl;
	show_ch(name, 32);
	cout << "���!" << endl;
	system("pause");
	return 0;
}
void show_ch(char *str, int n)
{
	++num;
	if (n == 0)
	{
		cout << str << endl;
	}
	else
		for (int i = 0; i < num; i++)
			cout << str << endl;
}