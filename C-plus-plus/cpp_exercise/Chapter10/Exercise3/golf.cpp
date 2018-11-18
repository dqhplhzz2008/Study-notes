#include <iostream>
#include <cstring>
#include "golf.h"
using namespace std;

Golf::Golf(const char * name, int hc)
{
	strncpy(fullname, name, 40);
	fullname[39] = '\0';
	handicap = hc;
}

Golf::~Golf()
{
	cout << "Bye!" << endl;
}

bool Golf::setGolf()
{
	char fullname[Len];
	int handicap;

	cout << "Please input the name of the golf player: ";
	cin.get(fullname, Len); 
	if (cin)
	{
		cout << "Please input the handicap of the golf player: ";
		cin >> handicap;
		cin.get();
		*this = Golf(fullname, handicap);
		return true;
	}
	else
		return false;

}

void Golf::sethandicap(int hc)
{
	handicap = hc;
}

void Golf::showGolf()const
{
	std::cout << "hullname: " << fullname << ", \thandicap: " << handicap << std::endl;
}