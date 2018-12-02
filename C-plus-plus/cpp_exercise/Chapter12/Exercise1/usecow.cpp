#include<iostream>
#include"cow.h"
using namespace std;

int main() {
	Cow c1;//默认构造函数
	cout << "C1的内容：" << endl;
	c1.ShowCow();
	Cow c2 = Cow("HAHA", "Walking", 36.6);
	cout << "C2的内容：" << endl;
	c2.ShowCow();
	Cow c3 = c2;//复制构造函数
	cout << "C3的内容：" << endl;
	c3.ShowCow();
	Cow c4;
	c4 = c2;//重载赋值符号
	cout << "C4的内容：" << endl;
	c4.ShowCow();

	system("pause");
	return 0;
}