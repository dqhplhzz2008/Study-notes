//C++ Primer Plus Edition 5
//Chapter 8 Homework 2
#include<iostream>
#include<string>
using namespace std;
struct CandyBar {
	string name;
	double weight;
	int hot;
};
void set_CandyBar(CandyBar &candy, char* n = "Millennium Munch", double w = 2.85, int h = 360);
void show_CandyBar(const CandyBar &c);
int main() {
	CandyBar candy;
	set_CandyBar(candy);
	show_CandyBar(candy);
	system("pause");
	return 0;
}

void set_CandyBar(CandyBar &c, char* n, double w, int h)
{
	c.name = n;
	c.weight = w;
	c.hot = h;

}
void show_CandyBar(const CandyBar &c)
{
	cout << "Name: " << c.name << endl;
	cout << "Weight: " << c.weight << endl;
	cout << "Hot: " << c.hot << endl;
}