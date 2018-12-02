#pragma once
#include<iostream>
#ifndef COM0_H_
using namespace std;
class complex {
	double a;
	double b;
public:
	complex();
	complex(double x, double y);
	~complex();
	complex operator+(const complex & t) const;
	complex operator-(const complex & t) const;
	friend complex operator*(const complex & t,double n);//Êý³Ë
	friend complex operator*(const complex & t1, const complex & t2);
	friend complex operator~(const complex & t);
	friend ostream & operator<<(ostream & os, const complex & c);
	friend istream & operator >> (istream &in, complex &c);


};
#endif // !COM0_H_
