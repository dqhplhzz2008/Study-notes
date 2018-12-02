#include "wine2.h"

/*
typedef valarray<int> ArrayInt;
typedef pair<ArrayInt, ArrayInt>PairArray;
string name;
PairArray year;
int SavYear;
*/
Wine::Wine(const char * l, int y, const int yr[], const int bot[])
{
	(string &)*this = l;
	SavYear = y;
	ArrayInt years(y);
	ArrayInt bottl(y);
	for (int i = 0; i < y; i++)
	{
		years[i] = yr[i];
		bottl[i] = bot[i];
	}
	(PairArray &)*this= make_pair(years, bottl);


}

Wine::Wine(const char * l, int y)
{
	(string &)*this = l;
	SavYear = y;
}

void Wine::GetBottles()
{
	cout << "Enter " << (string &)*this << " data for " << SavYear << " year(s):" << endl;
	PairArray & year = (PairArray&)(*this);//ѧϰ������
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
string & Wine::Label()
{
	return (string &)*this;
}

void Wine::Show()
{
	PairArray & year = (PairArray&)(*this);//ѧϰ������
	cout << "Wine: " << (string &)*this << endl;
	cout << "\tYear\tBottles" << endl;
	for (int i = 0; i < SavYear; i++)
	{
		cout << "\t" << year.first[i] << "\t" << year.second[i] << endl;
	}
}

int Wine::sum()
{
	PairArray & year = (PairArray&)(*this);//ѧϰ������
	return year.second.sum();
}
