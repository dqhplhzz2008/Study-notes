//C++ Primer Plus(5th Edition)
//Chapter 17 Exercise 2
//Designed by Yushuai Zhang
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cerr << "Usage: " << argv[0] << " filename[s]\n";
		//��������д��Ϊ���ܹ�������û�������ļ���ʱ���������
		//���ֱ��exit(EXIT_FAILURE)�˾��޷�������������
	}
	else {
		ofstream f;
		f.open(argv[1]);
		if (!f.is_open())
		{
			cerr << "Could not open " << argv[1] << endl;
			exit(EXIT_FAILURE);
		}
		cout << "Please input what you want to write into " << argv[0] << ": " << endl;
		string words;
		while (cin.fail() == false)
		{
			getline(cin, words);
			f << words;
		}
		cout << "Everything completed!" << endl;
		f.close();
	}
	system("pause");
	return 0;
}