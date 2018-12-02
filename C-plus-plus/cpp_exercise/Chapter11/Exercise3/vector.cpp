#include <cmath>
#include "vector.h"   // includes <iostream>
using std::sqrt;
using std::sin;
using std::cos;
using std::atan2;
using std::cout;

namespace VECTOR
{

	const double Rad_to_deg = 57.2957795130823;

	// private methods
	// calculates magnitude from x and y
	// set x from polar coordinate
	void Vector::set_x(double mag, double ang)
	{
		x = mag * cos(ang);
	}

	// set y from polar coordinate
	void Vector::set_y(double mag, double ang)
	{
		y = mag * sin(ang);
	}

	// public methods
	Vector::Vector()             // default constructor
	{
		x = y = 0.0;
		mode = 'r';
	}

	// construct vector from rectangular coordinates if form is r
	// (the default) or else from polar coordinates if form is p
	Vector::Vector(double n1, double n2, char form)
	{
		mode = form;
		if (form == 'r')
		{
			x = n1;
			y = n2;
		}
		else if (form == 'p')
		{
			set_x(n1, n2);
			set_y(n1, n2);
		}
		else
		{
			cout << "Incorrect 3rd argument to Vector() -- ";
			cout << "vector set to 0\n";
			x = y = 0.0;
			mode = 'r';
		}
	}

	// set vector from rectangular coordinates if form is r (the
	// default) or else from polar coordinates if form is p
	void Vector::set(double n1, double n2, char form)
	{
		mode = form;
		if (form == 'r')
		{
			x = n1;
			y = n2;
		}
		else if (form == 'p')
		{
			set_x(n1, n2);
			set_y(n1, n2);
		}
		else
		{
			cout << "Incorrect 3rd argument to Vector() -- ";
			cout << "vector set to 0\n";
			x = y = 0.0;
			mode = 'r';
		}
	}

	Vector::~Vector()    // destructor
	{
	}

	void Vector::polar_mode()    // set to polar mode
	{
		mode = 'p';
	}

	void Vector::rect_mode()     // set to rectangular mode
	{
		mode = 'r';
	}

	// operator overloading
	// add two Vectors
	Vector Vector::operator+(const Vector & b) const
	{
		return Vector(x + b.x, y + b.y);
	}

	// subtract Vector b from a
	Vector Vector::operator-(const Vector & b) const
	{
		return Vector(x - b.x, y - b.y);
	}

	// reverse sign of Vector
	Vector Vector::operator-() const
	{
		return Vector(-x, -y);
	}

	// multiple vector by n
	Vector Vector::operator*(double n) const
	{
		return Vector(n * x, n * y);
	}

	// friend methods
	// multiply n by Vector a
	Vector operator*(double n, const Vector & a)
	{
		return a * n;
	}

	// display rectangular coordinates if mode is r,
	// else display polar coordinates if mode is p
	std::ostream & operator<<(std::ostream & os, const Vector & v)
	{
		if (v.mode == 'r')
			os << "(x,y) = (" << v.x << ", " << v.y << ")";
		else if (v.mode == 'p')
		{
			os << "(m,a) = (" << v.magval() << ", "
				<< v.angval() * Rad_to_deg << ")";
		}
		else
			os << "Vector object mode is invalid";
		return os;
	}

}  // end namespace VECTOR
