//C++ Primer Plus Edition 5
//Chapter 8 Homework 1
#include<iostream>
using namespace std;
void show_ch(char *str, int n = 0);
int num = 0;
int main()
{
	char name[10] = "zhang";
	cout << "如果第二个参数为0，那么输出（这是第一次调用）：" << endl;
	show_ch(name);
	cout << "输出结束" << endl;
	cout << "第二次调用输出结果：" << endl;
	show_ch(name, 3);
	cout << "第三次调用输出结果：" << endl;
	show_ch(name, 9);
	cout << "第四次调用输出结果：" << endl;
	show_ch(name, 32);
	cout << "完成!" << endl;
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