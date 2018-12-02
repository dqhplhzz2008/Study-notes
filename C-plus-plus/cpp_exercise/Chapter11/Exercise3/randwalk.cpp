#include<iostream>
#include<cstdlib>
#include<ctime>
#include "vector.h"
using namespace std;
using VECTOR::Vector;
int main() {
	srand(time(0));
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;
	unsigned long max = 0;
	unsigned long min = 999;
	double avg = 0;
	int N;
	cout << "请输入测试的次数：N=";
	cin >> N;
	cout << "第一次：" << endl;
	int i;
	for (i = 0; i < N; i++)
	{
		cout << "Enter target distance(ONLY ENTER NUMBER): ";
		cin >> target;
		cout << "Enter step length: ";
		if (!(cin >> dstep))
			break;
		while (result.magval() < target)
		{
			direction = rand() % 360;
			step.set(dstep, direction, 'p');
			result = result + step;
			steps++;
		}
		if (max < steps)
			max = steps;
		if (min > steps)
			min = steps;
		avg += steps;
		result.polar_mode();
		steps = 0;
		result.set(0.0, 0.0);
	}
	avg /= N;
	cout << "max: " << max << endl << "min: " << min << endl << "average: " << avg << endl;
	cout << "Bye~";
	system("pause");
	return 0;
}  