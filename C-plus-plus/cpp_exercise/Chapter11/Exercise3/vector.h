// vect.h -- Vector class with <<, mode state
#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
namespace VECTOR
{
	class Vector
	{
	private:
		double x;          // horizontal value
		double y;          // vertical value
		char mode;         // 'r' = rectangular, 'p' = polar
						   // private methods for setting values
		void set_x(double mag, double ang);
		void set_y(double mag, double ang);
	public:
		Vector();
		Vector(double n1, double n2, char form = 'r');
		void set(double n1, double n2, char form = 'r');
		~Vector();
		double xval() const { return x; }       // report x value
		double yval() const { return y; }       // report y value
		double magval() const { return sqrt(x * x + y * y); }   // report magnitude
		double angval() const// report angle
		{
			if (x == 0.0 && y == 0.0)
				return 0.0;
			else
				return atan2(y, x);
		}
		
		void polar_mode();                    // set mode to 'p'
		void rect_mode();                     // set mode to 'r'
											  // operator overloading
		Vector operator+(const Vector & b) const;
		Vector operator-(const Vector & b) const;
		Vector operator-() const;
		Vector operator*(double n) const;
		// friends
		friend Vector operator*(double n, const Vector & a);
		friend std::ostream & operator<<(std::ostream & os, const Vector & v);
	};

}   // end namespace VECTOR
#endif
#pragma once
