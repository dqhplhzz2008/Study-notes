#include<iostream>
#include"cow.h"
using namespace std;

int main() {
	Cow c1;//Ĭ�Ϲ��캯��
	cout << "C1�����ݣ�" << endl;
	c1.ShowCow();
	Cow c2 = Cow("HAHA", "Walking", 36.6);
	cout << "C2�����ݣ�" << endl;
	c2.ShowCow();
	Cow c3 = c2;//���ƹ��캯��
	cout << "C3�����ݣ�" << endl;
	c3.ShowCow();
	Cow c4;
	c4 = c2;//���ظ�ֵ����
	cout << "C4�����ݣ�" << endl;
	c4.ShowCow();

	system("pause");
	return 0;
}