//C++ Primer Plus Edition 5
//Chapter 8 Homework 4
#include<iostream>
using namespace std;
#include<cstring>

struct stringy {
	char *str;
	int ct;
};
void show(const char *st, int n = 1);
void show(const stringy &strc, int n = 1);
void set(stringy& st, const char *t);

int main() {
	stringy beany;
	char testing[] = "Reality isn't what it used to be.";
	set(beany, testing);
	show(beany);
	show(beany, 2);
	testing[0] = 'D';
	testing[1] = 'u';
	show(testing);
	show(testing, 3);
	show("Done!");
	system("pause");
	return 0;
}

void set(stringy &st, const char *n)
{
	st.ct = strlen(n) + 1;
	st.str = new char[st.ct];
	strcpy(st.str, n);
}
void show(const stringy &strc, int n)
{
	for (int i = 0; i < n; i++)
		cout << strc.str << endl;
}

void show(const char *st, int n)
{
	for (int i = 0; i < n; i++) {
		if (strcmp(st, "Done!") == 0)
		{
			cout << "Done!" << endl;
			break;
		}
		cout << st << endl;

	}

}