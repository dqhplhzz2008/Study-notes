//C++ Primer Plus(5th Edition)
//Chapter 17 Exercise 4
//Designed by Yushuai Zhang
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;
int main()
{
	ifstream file1("text1.txt");
	ifstream file2("text2.txt");
	ofstream fileo("output.txt");
	if ((!file1.is_open())|| (!file2.is_open())|| (!fileo.is_open()))
	{
		cerr << "Could not open files, please confirm!" << endl;
		exit(EXIT_FAILURE);
	}
	string str1, str2;
	while (!file1.eof() && !file2.eof() && getline(file1, str1) && getline(file2, str2))
	{
		fileo << str1 << " " << str2 << endl;
	}
	while (getline(file1, str1))
		fileo << str1 << endl;
	while (getline(file2, str2))
		fileo << str2 << endl;
	file1.close();
	file2.close();
	fileo.close();
	cout << "Completed!" << endl;
	system("pause");
	return 0;
}