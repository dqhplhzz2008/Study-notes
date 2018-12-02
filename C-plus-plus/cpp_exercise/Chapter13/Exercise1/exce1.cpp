#include "exce1.h"

Cd::Cd(char * s1, char * s2, int n, double x)
{
	strcpy_s(performers, 50, s1);
	strcpy_s(label, 20, s2);
	selections = n;
	playtime = x;
}

Cd::Cd(const Cd & d)
{
	strcpy_s(performers, 50, d.performers);
	strcpy_s(label, 20, d.label);
	selections = d.selections;
	playtime = d.playtime;
}

Cd::Cd()
{
	strcpy_s(performers, 50, "null");
	strcpy_s(label, 20, "null");
	selections = 0;
	playtime = 0;
}

Cd::~Cd()
{
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
	strcpy_s(performers, 50, d.performers);
	strcpy_s(label, 20, d.label);
	selections = d.selections;
	playtime = d.playtime;
	return *this;

	// TODO: 在此处插入 return 语句
}

//Classic method
Classic::Classic(char * s0, char * s1, char * s2, int n, double x):Cd(s1,s2,n,x)
{
	strcpy_s(mainworks, 50, s0);
}

Classic::Classic(char * s0, const Cd & d): Cd(d)
{
	strcpy_s(mainworks, 50, s0);
}

Classic::Classic():Cd()
{
	strcpy_s(mainworks, 50, "null");
}

Classic::~Classic()
{
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
	strcpy_s(mainworks, 50, c.mainworks);
	return *this;
	// TODO: 在此处插入 return 语句
}
