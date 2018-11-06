#include<iostream>
using namespace std;
const int Max = 5;
int main() {
	int golf[Max];
	cout << "Please enter your golf scores.\n";
	cout << "Your must enter " << Max << " rounds.\n";
	int i;
	for (i = 0; i < Max; i++)
	{
		cout << "round #" << i + 1 << ": ";
		while (!(cin >> golf[i])) {
			cin.clear();//重置cin以接受新的输入
			while (cin.get() != '\n')
				continue;//删除错误输入，本质上是错误的输入不放到数组里面
			cout << "Please enter a number: ";//提示用户再输入
		}
	}
	double total = 0.0;
	for (i = 0; i < Max; i++)
		total += golf[i];
	cout << total / Max << " =average score " << Max << " rounds.\n";
	system("pause");
	return 0;
}