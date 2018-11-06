#include <stdio.h>
#include <iostream>
using namespace std;
int main()
{
	double height, weight,bmi,heiyc;
	const double mtoy = 39.37;
	cout << "请输入你的身高（单位为米）:" << endl;
	cin >> height;
	cout << "请输入你的体重（单位为千克）：" << endl;
	cin >> weight;
	bmi = height*height;
	bmi = weight / bmi;
	cout << "你的BMI为" << bmi << endl;
	heiyc = height *mtoy;
	cout << "你的身高为" << heiyc << "英寸。" << endl;
	system("pause");
	return 0;
}
