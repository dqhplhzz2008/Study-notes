//C++ Primer Plus Edition 5
//Chapter 6 Homework 7
#include<iostream>
#include<cctype>
#include<string>
using namespace std;
int main() {
	string word;
	char ch;
	int yuan = 0;
	int fu = 0;
	int others = 0;
	cin >> word;
	while (word != "q") {
		ch = word[0];
		if (isalpha(ch))
		{
			if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'
				|| ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
				++yuan;
			else
				++fu;
		}
		else
			++others;
		cin >> word;
	}
	cout << yuan << " words beginning with vowels." << endl;
	cout << fu << " words beginning with consonants." << endl;
	cout << others << " others." << endl;

	system("pause");
	return 0;
}