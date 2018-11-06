#include<fstream>
#include<iostream>
#include<cstdlib>
const int SIZE = 60;
using namespace std;
int main() {
	char filename[SIZE];
	ifstream f;
	cout << "Enter the name of data file: ";
	cin.getline(filename, SIZE);
	f.open(filename);
	if (!f.is_open())
	{
		cout << "Could not open the file" << filename << endl;
		cout << "Program Error, and terminating.\n";
		exit(EXIT_FAILURE);
	}
	double value;
	double sum = 0.0;
	int count = 0;
	f >> value;
	while (f.good())//��good()ֱ���ж��ǲ���ȫ������Ҫ�������жϳ���ԭ���������ȥ��д�жϴ�������
	{
		++count;
		sum += value;
		f >> value;
	}
	if (f.eof())
		cout << "End of file reached.\n";
	else if (f.fail())
		cout << "Input terminated by data mismatch.\n";
	else
		cout << "Input terminated for unknown reason.\n";
	if (count == 0)
		cout << "No data processed.\n";
	else {
		cout << "Items read: " << count << endl;
		cout << "Sum: " << sum << endl;
		cout << "Average: " << sum / count << endl;
	}
	f.close();
	system("pause");
	return 0;
}