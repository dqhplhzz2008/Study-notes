//C++ Primer Plus Edition 5
//Chapter 6 Homework 2
#include<iostream>
#include<cctype>
const int SIZE = 10;
using namespace std;
int main() {
	double donation[10];
	double average;
	int countbig = 0;
	int count=0;
	double sum = 0.0;
	cout << "Enter 10 numbers.If you want to quit, just input @:" << endl;
	for (int i = 0; i < SIZE; i++) {
		cin >> donation[i];
		if (cin.fail())
			break;
		else {
			sum += donation[i];
			++count;
		}
	}
	average = sum / count;
	cout << "The average number is: " << average << endl;
	for (int i = 0; i < count; i++) {
		if (donation[i] > average)
			++countbig;
	}
	cout << countbig << " numbers bigger than average.\n";
	
	system("pause");
	return 0;
}