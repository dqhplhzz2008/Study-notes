//C++ Primer Plus Edition 5
//Chapter 7 Homework 1
#include<iostream>
using namespace std;
double heaver(int m, int n);
int main() {
	double m, n, ans;
	cout << "Please input two numbers: ";
	cin >> m >> n;
	while (m != 0 && n != 0) {
		ans = heaver(m, n);
		cout << "The answer is " << ans << endl;
		cout << "Please input two numbers: ";
		cin >> m >> n;
	}

	cout << "Done!" << endl;
	system("pause");
	return 0;
}

double heaver(int m, int n) {
	double res;
	res = 2.0*m*n / (m + n);
	return res;
}