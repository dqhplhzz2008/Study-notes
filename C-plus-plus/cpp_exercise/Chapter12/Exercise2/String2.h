#pragma once
#include <iostream>
using std::ostream;
using std::istream;

#ifndef STRING1_H_
#define STRING1_H_
class String
{
private:
	char * str;             // pointer to string
	int len;                // length of string
	static int num_strings; // number of objects
	static const int CINLIM = 80;  // cin input limit
public:
	// constructors and other methods
	String(const char * s); // 构造函数
	String();               // 默认构造函数
	String(const String &); // 复制构造函数
	~String();              // 析构函数
	int length() const { return len; }
	void stringlow();
	void stringbig();
	int cishu(char ch) const;
	// 重载操作符
	String & operator=(const String &);
	String & operator=(const char *);
	char & operator[](int i);
	const char & operator[](int i) const;
	String operator+(const String & s) const;
	String operator+(const char * s) const;
	// 重载友元操作符函数
	friend bool operator<(const String &st, const String &st2);
	friend bool operator>(const String &st1, const String &st2);
	friend bool operator==(const String &st, const String &st2);
	friend ostream & operator<<(ostream & os, const String & st);
	friend istream & operator >> (istream & is, String & st);
	friend String operator+(const char * st1, const String & st2);
	// static function
	static int HowMany();
};
#endif
