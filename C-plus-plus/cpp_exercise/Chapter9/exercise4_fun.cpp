#include<iostream>
#include "exercise4.h"
namespace SALES
{
	void setSales(Sales & s)
	{
		using std::cin;
		using std::cout;
		using std::endl;

		cout << "Enter sales:" << endl;
		for (int i = 0; i < QUARTERS; ++i)
		{
			cout << "sales[" << i << "]: ";
			cin >> s.sales[i];
		}

		// get average, max, min
		double sum = 0.0;
		double max = s.sales[0], min = s.sales[0];
		for (int i = 0; i < QUARTERS; ++i)
		{
			double cur = s.sales[i];
			if (cur > max)
				max = cur;
			if (cur < min)
				min = cur;
			sum += cur;
		}
		s.average = sum / (float)QUARTERS;
		s.max = max;
		s.min = min;
	}

	void showSales(const Sales & s)
	{
		using std::cout;
		using std::endl;

		// show sales
		cout << "SALES: ";
		for (int i = 0; i < QUARTERS; ++i)
			cout << s.sales[i] << " ";
		cout << endl;

		// show average
		cout << "AVERAGE: " << s.average << endl;

		// show max and min
		cout << "MAX: " << s.max << endl;
		cout << "MIN: " << s.min << endl;
	}
}