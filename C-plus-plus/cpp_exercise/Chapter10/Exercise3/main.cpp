#include <iostream>
#include "golf.h"
using namespace std;
int main()
{
	Golf one;
	Golf two;
	Golf three;

	one.showGolf();         // Ĭ�Ϲ��캯��
	two.setGolf();          // �����汾
	two.showGolf();
	two.sethandicap(5000);  //��Ա����
	two.showGolf();         //��Ա����
	three.sethandicap(20);
	three.showGolf();
	system("pause");
	return 0;
}