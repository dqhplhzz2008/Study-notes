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
	//set使用set_union的时候，最后一个参数不能直接使用Bothb.begin()，否则会报错（assignment of read-only localtion），应该使用入上所示的方法
	//vector使用set_union的时候，最后一个参数应该这样用：back_inserter(c)，否则会报错-Segmentation fault (core dumped)
	cout << "The list of Mat's and Pat's friends: " << endl;
	copy(Bothb.begin(), Bothb.end(), out);
	cout << endl;
	system("pause");
	return 0;


	
}
