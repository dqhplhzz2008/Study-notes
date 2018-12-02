#ifndef COW_H_
#define COW_H_
using namespace std;

class Cow {
	char name[20];
	char * hobby;
	double weight;
public:
	Cow();
	Cow(const char*nm, const char * ho, double wt);
	Cow(const Cow &);
	~Cow();
	Cow & operator=(const Cow & c);
	void ShowCow()const;
};
#endif // !COW_H_
#pragma once
