#include<iostream>
#include<string>
using namespace std;
int main() {
	string name;
	string dessert;

	cout << "Enter your name: \n";
	getline(cin, name);//����string������ո��һ�е�ʱ��Ҫ��getline���ַ�ʽ���С�
	//cin�ǲ�����ָ��������ȥ������롣
	cout << "Enter your favorite dessert: \n";
	getline(cin, dessert);
	cout << "I have some delicious " << dessert;
	cout << " for you, " << name << ".\n";
	system("pause");
	return 0;
}