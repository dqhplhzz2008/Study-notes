#include<fstream>
#include<iostream>
using namespace std;
int main() {
	char automobile[50];
	int year;
	double a_price;
	double d_price;
	ofstream f;
	f.open("carinfo.txt");//打开空白文件，没有文件就创建文件
	cout << "Enter the make and model of automobile: ";
	cin.getline(automobile, 50);
	cout << "Enter the model year: ";
	cin >> year;
	cout << "Enter the original asking price:";
	cin >> a_price;
	d_price = 0.913*a_price;

	cout << fixed;
	cout.precision(2);//小数位2位
	cout.setf(ios_base::showpoint);
	cout << "Make and model: " << automobile << endl;
	cout << "Year:" << year << endl;
	cout << "Was asking $" << a_price << endl;
	cout << "Now asking $" << d_price << endl;

	f << fixed;
	f.precision(2);
	f.setf(ios_base::showpoint);
	f << "Make and model: " << automobile << endl;
	f << "Year:" << year << endl;
	f << "Was asking $" << a_price << endl;
	f << "Now asking $" << d_price << endl;
	f.close();
	system("pause");
	return 0;
}