#include "exce1.h"

Cd::Cd(char * s1, char * s2, int n, double x)
{
	performers = new char[strlen(s1) + 1];
	label = new char[strlen(s2) + 1];
	strcpy_s(performers, strlen(s1) + 1, s1);
	strcpy_s(label, strlen(s2) + 1, s2);
	selections = n;
	playtime = x;
}

Cd::Cd(const Cd & d)
{
	performers = new char[strlen(d.performers) + 1];
	label = performers = new char[strlen(d.label) + 1];
	strcpy_s(performers, strlen(d.performers) + 1, d.performers);
	strcpy_s(label, strlen(d.label) + 1, d.label);
	selections = d.selections;
	playtime = d.playtime;
}

Cd::Cd()
{
	performers = new char[5];
	strcpy_s(performers, 5, "null");
	label = new char[5];
	strcpy_s(label, 5, "null");
	selections = 0;
	playtime = 0.0;
}

Cd::~Cd()
{
	delete[] performers;
	delete[] label;
}

void Cd::Report() const
{
	cout << "Performers: " << performers << endl;
	cout << "Label: " << label << endl;
	cout << "Selections: " << selections << endl;
	cout << "Playtime: " << playtime << endl;
}

Cd & Cd::operator=(const Cd & d)
{
	if (this == &d)
		return *this;
	delete [] performers;
	delete[] label;
	performers = new char[strlen(d.performers) + 1];
	label = performers = new char[strlen(d.label) + 1];
	strcpy_s(performers, strlen(d.performers) + 1, d.performers);
	strcpy_s(label, strlen(d.label) + 1, d.label);
	selections = d.selections;
	playtime = d.playtime;
	return *this;

	// TODO: 在此处插入 return 语句
}

//Classic method
Classic::Classic(char * s0, char * s1, char * s2, int n, double x):Cd(s1,s2,n,x)
{
	mainworks = new char[strlen(s0) + 1];
	strcpy_s(mainworks, strlen(s0) + 1, s0);
}

Classic::Classic(char * s0, const Cd & d): Cd(d)
{
	mainworks = new char[strlen(s0) + 1];
	strcpy_s(mainworks, strlen(s0) + 1, s0);
}

Classic::Classic():Cd()
{
	mainworks = new char[5];
	strcpy_s(mainworks, 5, "null");
}

Classic::~Classic()
{
	delete[] mainworks;
}

void Classic::Report() const
{
	cout<<"The main works of this disk are " << mainworks << endl; 
	Cd::Report();
}

Classic & Classic::operator=(const Classic & c)
{
	if (this == &c)
		return *this;
	Cd::operator=(c);
	mainworks = new char[strlen(c.mainworks) + 1];
	strcpy_s(mainworks, strlen(c.mainworks) + 1, c.mainworks);
	return *this;
	// TODO: 在此处插入 return 语句
}
