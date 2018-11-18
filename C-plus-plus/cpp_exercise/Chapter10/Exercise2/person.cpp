#include<iostream>
#include<string>
#include<cstring>
using namespace std;
const int LIMIT = 25;
class Person {
private:
	string lname;
	char fname[LIMIT];
public:
	Person();
	Person(const string &ln, const char*fn = "Heyyou");
	void Show() const;
	void FormalShow() const;
};
Person::Person()
{
	lname = "";
	fname[0] = '\0';

}
Person::Person(const string & ln, const char *fn) {
	lname = ln;
	strncpy(fname, fn, LIMIT-1);
	fname[LIMIT - 1] = '\0';

}
void Person::Show()const {
	cout << fname << " " << lname << endl;

}

void Person::FormalShow() const {
	cout << lname << " " << fname << endl;

}
int main() {
	Person one;
	Person two("Smythecraft");
	Person three("Dimwiddy", "Sam");
	one.Show();
	cout << endl;
	one.FormalShow();
	cout << endl;
	two.FormalShow();
	cout << endl;
	three.Show();
	system("pause");
	return 0;
}