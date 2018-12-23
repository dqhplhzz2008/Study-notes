//C++ Primer Plus(5th Edition)
//Chapter 17 Exercise 3
//Designed by Yushuai Zhang
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		cerr << "Usage: " << argv[0] << " sourcefile targetfile\n";
		//��������д��Ϊ���ܹ�������û�������ļ���ʱ���������
		//���ֱ��exit(EXIT_FAILURE)�˾��޷�������������
	}
	else {
		
		ifstream fin;//��ȡ�ļ����ݣ�д�뵽�ڴ����ļ��ĳ�ʼ��
		fin.open(argv[1]);
		ofstream f;	//������д���ļ��ĳ�ʼ��
		f.open(argv[2]);
		if ((!f.is_open())||(!fin.is_open()))
		{
			cerr << "Could not open files, please confirm!" << endl;
			exit(EXIT_FAILURE);
		}
		string words;
		while (getline(cin, words))
			f << words << endl;
		f.close();
		fin.close();
		cout << "Everything completed!" << endl;
	}
	system("pause");
	return 0;
}