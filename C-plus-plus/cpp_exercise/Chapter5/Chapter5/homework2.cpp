#include<iostream>
#include<cstring>
using namespace std;
int main() {
	int i;
	int count=0;
	cout << "Enter number:" << endl;
	cin >> i;
	while (i != 0)
	{
		count += i;
		cout <<"��Ŀǰ�ĺ�Ϊ" << count << endl;
		cin >> i;
	}
	system("pause");
	return 0;
}