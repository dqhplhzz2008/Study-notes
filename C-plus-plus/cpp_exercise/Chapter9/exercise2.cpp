#include<iostream>
#include<string>
#include<cstring>
using namespace std;
const int ArSize = 10;
void strcount(const string & str);

int main() {

	string str;
	cout << "Enter a line: \n";
	getline(cin, str);
	while (str != "") {
		strcount(str);
		cout << "Enter next line(empty line to quit): \n";
		getline(cin, str);
	}
	cout << "Bye\n";
	system("pause");
	return 0;
}


void strcount(const string & str){

	using namespace std;
	static int total = 0;
	int count = 0;
	cout << "\"" << str << "\" contains ";
	count = str.length();
	total += count;
	cout << count << " characters\n";
	cout << total << " characters total\n";
}