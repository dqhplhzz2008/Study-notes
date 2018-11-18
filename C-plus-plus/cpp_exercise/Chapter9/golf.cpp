#include<iostream>
#include <string>
#include <cstring>
#include"golf.h"
using namespace std;
void setgolf(golf & g, const char *name, int hc)
{
	strcpy(g.fullname, name);
	g.handicap = hc;
}
int setgolf(golf & g)
{
	cout << "Please enter the full name of golf player: ";
	cin.getline(g.fullname, Len);
	if (strcmp(g.fullname, "") == 0)
	{
		return 0;
	}

	cout << "Please enter the hanicap of golf player: ";
	cin >> g.handicap;
	cin.get();

	return 1;
}

void handicap(golf & g, int hc)
{
	g.handicap = hc;
}

void showgolf(const golf & g)
{
	cout << "Here is the golf contents:\n";
	cout << "Name: " << g.fullname << endl;
	cout << "Handicap: " << g.handicap << endl;
}