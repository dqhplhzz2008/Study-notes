#include<iostream>
#include<cstring>
using namespace std;
int main() {
	int a, b;
	int sum = 0;
	cout << "Enter two number:" << endl;
	cin >> a >> b;
	if (a < b)
	{
		for (int i = a; i <= b; i++)
			sum += i;
	}
	else if (a > b)
	{
		for (int i = b; i <= a; i++)
			sum += i;
	}
	cout << sum << endl;
	system("pause");
	return 0;
}