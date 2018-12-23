//C++ Primer Plus(5th Edition)
//Chapter 17 Exercise 7
//Modified by Yushuai Zhang
#include <iostream>  
#include <fstream>  
#include <string>  
#include <vector>  
#include <algorithm>  
#include <cstdlib>

void ShowStr(const std::string & str)
{
	std::cout << str << std::endl;
}
class Store
{
	std::ofstream & of;
public:
	Store(std::ofstream &out) :of(out) {}
	void operator()(const std::string &str)
	{
		size_t len = str.size();
		of.write((char*)&len, sizeof(std::size_t));
		of.write(str.data(), len);
	}
};

void GetStrs(std::ifstream &is, std::vector<std::string> &vec)
{
	size_t len;
	while (is.read((char *)&len, sizeof(size_t)))
	{
		char *st = new char[len];
		is.read(st, len);
		st[len + 1] = '\0';
		vec.push_back(st);
	}
}
int main()
{
	using namespace std;
	vector<string> vostr;
	string temp;

	cout << "Enter strings (empty line to quit):\n";
	while (getline(cin, temp) && temp[0] != '\0')
		vostr.push_back(temp);
	cout << "Here is your input.\n";
	for_each(vostr.begin(), vostr.end(), ShowStr);

	ofstream fout("strings.txt", ios_base::out | ios_base::binary);
	for_each(vostr.begin(), vostr.end(), Store(fout));
	fout.close();

	vector<string> vistr;
	ifstream fin("strings.txt", ios_base::in | ios_base::binary);
	if (!fin.is_open())
	{
		cerr << "Could not open file for input.\n";
		exit(EXIT_FAILURE);
	}
	GetStrs(fin, vistr);
	cout << "\nHere are the strings read form the file:\n";
	for_each(vistr.begin(), vistr.end(), ShowStr);
	system("pause");
	return 0;
}