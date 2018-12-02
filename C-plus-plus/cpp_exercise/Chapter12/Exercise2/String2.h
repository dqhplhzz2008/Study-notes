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
	String(const char * s); // ���캯��
	String();               // Ĭ�Ϲ��캯��
	String(const String &); // ���ƹ��캯��
	~String();              // ��������
	int length() const { return len; }
	void stringlow();
	void stringbig();
	int cishu(char ch) const;
	// ���ز�����
	String & operator=(const String &);
	String & operator=(const char *);
	char & operator[](int i);
	const char & operator[](int i) const;
	String operator+(const String & s) const;
	String operator+(const char * s) const;
	// ������Ԫ����������
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
