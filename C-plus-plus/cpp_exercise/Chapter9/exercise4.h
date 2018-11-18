#pragma once
#ifndef SALES_H_
#define SALES_H_
namespace SALES {
	const int QUARTERS = 4;
	struct Sales
	{
		double sales[QUARTERS];
		double average;
		double max;
		double min;
	};
	void setSales(Sales &s);
	void showSales(const Sales &s);
}
#endif
