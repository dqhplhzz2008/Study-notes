/*
char name[20];
char * hobby;
double weight;*/
#include <iostream>
#include "cow.h"
using namespace std;
Cow::Cow() {
	name[0] = '\0';
	hobby = new char[5];
	strcpy(hobby, "NULL");
	weight = 0.0;

}
Cow::Cow(const char*nm, const char * ho, double wt)
{
	strcpy(name, nm);
	int len1 = strlen(ho);
	hobby = new char[len1 + 1];
	strcpy(hobby, ho);
	weight = wt;
}
Cow::Cow(const Cow &c)
{
	strcpy(name, c.name);
	int len2 = strlen(c.hobby);
	hobby = new char[len2 + 1];
	strcpy(hobby, c.hobby);
	weight = c.weight;

}
Cow::~Cow()
{
	delete[] hobby;

}
Cow & Cow::operator=(const Cow & c) {
	if (this == &c)
		return *this;
	strcpy(name, c.name);
	delete[] hobby;
	int len3;
	len3 = strlen(c.hobby);
	hobby = new char[len3];
	strcpy(hobby, c.hobby);
	weight = c.weight;
	return *this;

}
void Cow::ShowCow()const {
	cout << "Name: " << name << endl;
	cout << "Hobby: " << hobby << endl;
	cout << "Weight: " << weight << endl;

}