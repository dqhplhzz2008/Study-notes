#include <iostream>
#include "golf.h"
using namespace std;
int main()
{
	Golf one;
	Golf two;
	Golf three;

	one.showGolf();         // 默认构造函数
	two.setGolf();          // 交互版本
	two.showGolf();
	two.sethandicap(5000);  //成员函数
	two.showGolf();         //成员函数
	three.sethandicap(20);
	three.showGolf();
	system("pause");
	return 0;
}