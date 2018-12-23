//C++ Primer Plus(5th Edition)
//Chapter 16 Exercise 7
//Designed by Yushuai Zhang
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;
vector<int> lotto(int point, int yuan);
void Show(int);
int main()
{
	vector<int>winners;
	int pnum, times;
	cout << "Please enter the number of points: ";
	cin >> pnum;
	cout << "Please enter the number of zhongjiang: ";
	cin >> times;
	winners = lotto(pnum, times);
	for_each(winners.begin(), winners.end(), Show);
	system("pause");
	return 0;

}

vector<int>lotto(int point, int yuan)
{
	vector<int>temp;


}
void Show(int v)
{
	cout << v << ' ';
}

