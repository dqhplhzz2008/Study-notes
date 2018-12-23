//C++ Primer Plus(5th Edition)
//Chapter 16 Exercise 8
//Designed by Yushuai Zhang
#include<iostream>
#include<string>
#include<set>
#include<algorithm>
#include<iterator>
using namespace std;

int main()
{
	ostream_iterator<string, char>out(cout, " ");
	string Mat[6] = { "David","Yushuai","Zhang","Mercix","Haoran","Haha" };
	string Pat[8] = { "Zhang","Haoran","Xinzi","AAA","Haha","Qiman","Main","Cougoule" };
	set<string>Matb(Mat, Mat + 6);
	set<string>Patb(Pat, Pat + 8);
	cout << "Mat's friends:\n";
	copy(Matb.begin(), Matb.end(), out);
	cout << endl;
	cout << "Pat's friends:\n";
	copy(Patb.begin(), Patb.end(), out);
	cout << endl;
	set<string>Bothb;
	set_union(Matb.begin(), Matb.end(), Patb.begin(), Patb.end(), inserter(Bothb,Bothb.begin()));
	//setʹ��set_union��ʱ�����һ����������ֱ��ʹ��Bothb.begin()������ᱨ��assignment of read-only localtion����Ӧ��ʹ��������ʾ�ķ���
	//vectorʹ��set_union��ʱ�����һ������Ӧ�������ã�back_inserter(c)������ᱨ��-Segmentation fault (core dumped)
	cout << "The list of Mat's and Pat's friends: " << endl;
	copy(Bothb.begin(), Bothb.end(), out);
	cout << endl;
	system("pause");
	return 0;


	
}
