//C++ Primer Plus(5th Edition)
//Chapter 15 Exercise 2
//Modefied By Yushuai Zhang
#include <iostream>
#include<stdexcept>
#include<string>
//学习logic_error的这种使用方法，利用explicit，然后将字符串s通过初始化列表直接给logic_error()就可以了，自然就到了what里面
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

