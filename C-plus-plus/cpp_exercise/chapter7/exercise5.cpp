//C++ Primer Plus Edition 5
//Chapter 7 Homework 5
#include<iostream>
using namespace std;
int factorial(int n);
int main() {
	int n, ans;
	cout << "Please input an integer: ";
	cin >> n;
	ans = factorial(n);
	cout << "The answer is " << ans << endl;
	system("pause");
	return 0;
}
int factorial(int n) {
	int res = 1;
	if (n > 1)
		res = n*factorial(n-1);
	return res;
}