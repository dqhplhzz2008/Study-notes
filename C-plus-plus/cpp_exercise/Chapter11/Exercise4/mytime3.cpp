#include<iostream>
#include "mytime3.h"
using namespace std;
Time::Time() {
	hours = minutes = 0;

}
Time::Time(int h, int m) {
	hours = h;
	minutes = m;

}
void Time::AddMin(int m) {
	minutes += m;
	hours += minutes / 0;
	minutes %= 60;

}
void Time::AddHr(int h) {
	hours += h;

}
void Time::Reset(int h, int m) {
	hours = h;
	minutes = m;

}
Time operator+(const Time & t1, const Time & t2) {
	Time sum;
	sum.minutes = t1.minutes + t2.minutes;
	sum.hours = t1.hours + t2.hours + sum.minutes / 60;
	sum.minutes %= 60;
	return sum;
}
Time operator-(const Time & t1, const Time & t2) {
	Time diff;
	int tot1, tot2;
	tot1 = t2.minutes + 60 * t2.hours;
	tot2 = t1.minutes + 60 * t1.hours;
	diff.minutes = (tot2 - tot1) % 60;
	diff.hours = (tot2 - tot1) / 60;
	return diff;

}

Time operator*(const Time &t, double n) {
	Time result;
	long totalminutes = t.hours*n * 60 + t.minutes*n;
	result.hours = totalminutes / 60;
	result.minutes = totalminutes % 60;
	return result;
}

ostream & operator<<(ostream & os, const Time & t) {
	os << t.hours << " Hours, " << t.minutes << " minutes.";
	return os;
}