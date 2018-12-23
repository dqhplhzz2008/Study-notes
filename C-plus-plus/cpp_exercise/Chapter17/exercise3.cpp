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
		//故意这样写是为了能够测试在没有输入文件的时候的输出结果
		//如果直接exit(EXIT_FAILURE)了就无法看到输出结果了
	}
	else {
		
		ifstream fin;//读取文件内容，写入到内存中文件的初始化
		fin.open(argv[1]);
		ofstream f;	//把内容写入文件的初始化
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