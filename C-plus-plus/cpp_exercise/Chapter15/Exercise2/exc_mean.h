//C++ Primer Plus(5th Edition)
//Chapter 15 Exercise 2
//Modefied By Yushuai Zhang
#include <iostream>
#include<stdexcept>
#include<string>
//ѧϰlogic_error������ʹ�÷���������explicit��Ȼ���ַ���sͨ����ʼ���б�ֱ�Ӹ�logic_error()�Ϳ����ˣ���Ȼ�͵���what����
class bad_hmean: public std::logic_error
{
public:
	explicit bad_hmean(const std::string& s) :logic_error(s) {}
};


class bad_gmean: public std::logic_error
{
public:
	explicit bad_gmean(const std::string& s) :logic_error(s) {}
};

