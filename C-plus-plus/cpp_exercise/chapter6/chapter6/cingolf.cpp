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
			cin.clear();//����cin�Խ����µ�����
			while (cin.get() != '\n')
				continue;//ɾ���������룬�������Ǵ�������벻�ŵ���������
			cout << "Please enter a number: ";//��ʾ�û�������
		}
	}
	double total = 0.0;
	for (i = 0; i < Max; i++)
		total += golf[i];
	cout << total / Max << " =average score " << Max << " rounds.\n";
	system("pause");
	return 0;
}