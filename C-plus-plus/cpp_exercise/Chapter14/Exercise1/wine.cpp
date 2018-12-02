#include "wine.h"

/*
typedef valarray<int> ArrayInt;
typedef pair<ArrayInt, ArrayInt>PairArray;
string name;
PairArray year;
int SavYear;
*/
Wine::Wine(const char * l, int y, const int yr[], const int bot[])
{
	name = l;
	SavYear = y;
	ArrayInt years(y);
	ArrayInt bottl(y);
	for (int i = 0; i < y; i++)
	{
		years[i] = yr[i];
		bottl[i] = bot[i];
	}
	year = make_pair(years, bottl);//pair����ϣ����ס
}

Wine::Wine(const char * l, int y)
{
	name = l;
	SavYear = y;
}

void Wine::GetBottles()
{
	cout << "Enter " << name << " data for " << SavYear << " year(s):" << endl;
	year.first.resize(SavYear);
	year.second.resize(SavYear);//valarray����ĳ�Ա�����úú�ѧѧ
	for (int i = 0; i < SavYear; i++)
	{
		cout << "Enter year: ";
		cin >> year.first[i];
		cout << "Enter bottles for that year: ";
		cin >> year.second[i];
	}
}

void Wine::Show()
{
	cout << "Wine: " << name << endl;
	cout << "\tYear\tBottles" << endl;
	for (int i = 0; i < SavYear; i++)
	{
		cout << "\t" << year.first[i] << "\t" << year.second[i] << endl;
	}
}

int Wine::sum()
{
	return year.second.sum();
}
