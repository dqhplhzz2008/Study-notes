#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
	double height, weight,bmi,heiyc;
	const double mtoy = 39.37;
	cout << "�����������ߣ���λΪ�ף�:" << endl;
	cin >> height;
	cout << "������������أ���λΪǧ�ˣ���" << endl;
	cin >> weight;
	bmi = height*height;
	bmi = weight / bmi;
	cout << "���BMIΪ" << bmi << endl;
	heiyc = height *mtoy;
	cout << "������Ϊ" << heiyc << "Ӣ�硣" << endl;
	system("pause");
	return 0;
}
