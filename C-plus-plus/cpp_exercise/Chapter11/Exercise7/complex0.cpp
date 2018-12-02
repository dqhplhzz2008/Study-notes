#include "complex0.h"
#include<iostream>
complex::complex() {
	a = 0;
	b = 0;
}
complex::complex(double x, double y) {
	a = x;
	b = y;

}
complex::~complex() {}
complex complex::operator+(const complex & t) const
{
	
	complex sum;
	sum.a = a + t.a;
	sum.b = b + t.b;
	return sum;

}
complex complex::operator-(const complex & t) const
{
	complex diff;
	diff.a = a - t.a;
	diff.b = b - t.b;
	return diff;

}
complex operator*(const complex & t, double n)  //Êý³Ë
{
	return complex((t.a)*n, (t.b)*n);

}
	
complex operator*(const complex & t1, const complex & t2)
{
	return complex((t1.a*t2.a - t1.b*t2.b), (t1.a*t2.b + t1.b*t2.a));

}
complex operator~(const complex & t)
{
	return complex(t.a, (-1.0)*t.b);

}
ostream & operator<<(ostream & os, const complex & c)
{
	os << "(" << c.a << "," << c.b << "!" << ")";
	return os;

}
istream & operator >> (istream &in, complex &c)
{
	in >> c.a >> c.b;
	return in;
}
