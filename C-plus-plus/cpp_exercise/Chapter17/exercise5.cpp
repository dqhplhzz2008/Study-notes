//C++ Primer Plus(5th Edition)
//Chapter 17 Exercise 5
//Designed by Yushuai Zhang
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<set>
#include<algorithm>
#include<iterator>
using namespace std;

int main()
{
	ostream_iterator<string, char>out(cout, " ");
	ifstream file1("mat.dat");
	ifstream file2("pat.dat");
	ofstream fileo("matnpat.dat");
	if (!file1.is_open() || !file2.is_open())
	{
		cout << "Open files error. Please confirm!\n";
		//exit(EXIT_FAILURE);
		system("pause");
		return 0;
	}
	set<string> setmat;
	set<string> setpat;
	string temp;
	while (getline(file1, temp))
		setmat.insert(temp);
	while (getline(file2, temp))
		setpat.insert(temp);
	cout << "Mat's friends:\n";
	copy(setmat.begin(), setmat.end(), out);
	cout << endl;
	cout << "Pat's friends:\n";
	copy(setpat.begin(), setpat.end(), out);
	cout << endl;
	set<string>Bothb;
	set_union(setmat.begin(), setmat.end(), setpat.begin(), setpat.end(), inserter(Bothb, Bothb.begin()));
	//setʹ��set_union��ʱ�����һ����������ֱ��ʹ��Bothb.begin()������ᱨ��assignment of read-only localtion����Ӧ��ʹ��������ʾ�ķ���
	//vectorʹ��set_union��ʱ�����һ������Ӧ�������ã�back_inserter(c)������ᱨ��-Segmentation fault (core dumped)
	cout << "The list of Mat's and Pat's friends: " << endl;
	copy(Bothb.begin(), Bothb.end(), out);
	cout << endl;
	for each(string var in Bothb)
		fileo << var << endl;
	file1.close();
	file2.close();
	fileo.close();
	system("pause");
	return 0;
}