#include <cstring>
#include "vp.h"

Port::Port(const char * br, const char * st, int b)
{
	brand = new char[strlen(br) + 1];
	strcpy_s(brand, strlen(br) + 1, br);
	strcpy_s(style, 20, st);
	bottles = b;
}

Port::Port(const Port & p)
{
	brand = new char[strlen(p.brand) + 1];
	strcpy_s(brand, strlen(p.brand) + 1, p.brand);
	strcpy_s(style, 20, p.style);
	bottles = p.bottles;
}

Port & Port::operator=(const Port & p)
{
	if(this == & p)
		return *this;
	delete[] brand;
	brand = new char[strlen(p.brand) + 1];
	strcpy_s(brand, strlen(p.brand) + 1, p.brand);
	strcpy_s(style, 20, p.style);
	bottles = p.bottles;
	return *this;
	// TODO: 在此处插入 return 语句
}

Port & Port::operator+=(int b)
{
	bottles += b;
	return *this;
	// TODO: 在此处插入 return 语句
}

Port & Port::operator-=(int b)
{
	bottles -= b;
	return *this;
	// TODO: 在此处插入 return 语句
}

void Port::Show() const
{
	cout << "Brand: " << brand << endl;
	cout << "Kind: " << style << endl;
	cout << "Bottles: " << bottles << endl;
}

ostream & operator<<(ostream & os, const Port & p)
{
	os << p.brand << ", " << p.style << ", " << p.bottles;
	return os;
	// TODO: 在此处插入 return 语句
}



//VintagePort methods

VintagePort::VintagePort()
{
	nickname = new char[5];
	strcpy_s(nickname, 5, "none");
	year = 0;
}

VintagePort::VintagePort(const char * br, int b, const char * nn, int y):Port(br, "Vintage", b)
{
	nickname = new char[strlen(nn) + 1];
	strcpy_s(nickname, strlen(nn) + 1, nn);
	year = y;
}

VintagePort::VintagePort(const VintagePort & vp)
{
	nickname = new char[strlen(vp.nickname) + 1];
	strcpy_s(nickname, strlen(vp.nickname) + 1, vp.nickname);
	year = vp.year;
}

VintagePort & VintagePort::operator=(const VintagePort & vp)
{
	nickname = new char[strlen(vp.nickname) + 1];
	strcpy_s(nickname, strlen(vp.nickname) + 1, vp.nickname);
	year = vp.year;
	return *this;
	// TODO: 在此处插入 return 语句
}

void VintagePort::Show() const
{
	Port::Show();
	cout << "Nickname: " << nickname << endl;
	cout << "Year: " << year << endl;
}
ostream & operator<<(ostream & os, const VintagePort & vp)
{
	os << (const Port &)vp;//强制类型转换，务必要做，不然出错
	os << ", " << vp.nickname << ", " << vp.year;
	return os;
	// TODO: 在此处插入 return 语句
}
