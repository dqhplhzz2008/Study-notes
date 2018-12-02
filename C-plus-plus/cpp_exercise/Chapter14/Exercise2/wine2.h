#ifndef WINE_H_
#define WINE_H_
#include<iostream>
#include<cstring>
#include <cstdlib>
#include <valarray>
#include <string>
using namespace std;
typedef valarray<int> ArrayInt;
typedef pair<ArrayInt, ArrayInt>PairArray;
class Wine : private string, private PairArray
{
private:
	int SavYear;
public:
	Wine(const char*l, int y, const int yr[], const int bot[]);
	Wine(const char*l, int y);
	void GetBottles();
	void Show();
	string & Label();
	int sum();

};
#endif // !WINE_H_