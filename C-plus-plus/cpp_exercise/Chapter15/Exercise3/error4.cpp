//C++ Primer Plus(5th Edition)
//Chapter 15 Exercise 3
//Modefied By Yushuai Zhang
#include <iostream>
#include <cmath> 
#include<string>
/*
要由logic_error类引出，先写一个logic_error类，然后定义要重载的成员函数为虚函数，也就是这里的show_error。
要显示输入的两个参数，因此要将logic_error设置两个成员变量，由于继承类中要使用，所以设置为protected
然后在两个派生类中这样写就可以了。由于两个派生类都是继承于logic_error，因此可以把catch到的定义为logic_error类，然后根据
实际是什么类再进行处理
*/
class logic_error
{
protected:
	double v1;
	double v2;
public:
	logic_error(double a = 0, double b = 0) :v1(a), v2(b) {};
	virtual void show_error() {};

};
class bad_hmean : public logic_error
{
public:
	virtual void show_error()
	{
		std::cout << "bad argument to hmean(),invalid argument,your input are " << logic_error::v1 << " and " 
			<< logic_error::v2 << ", a=-b.\n" << std::endl;
	}
	bad_hmean(double a=0,double b=0) :logic_error(a, b) {}
};


class bad_gmean : public logic_error
{
public:
	virtual void show_error()
	{
		std::cout << "bad argument to gmean(),invalid argument,your input are " << logic_error::v1 << " and " << logic_error::v2 
			<< ", both of them shoule be >=0\n.\n" << std::endl;
	}
	bad_gmean(double a = 0, double b = 0) :logic_error(a, b) {};
};
// function prototypes
double hmean(double a, double b) throw(bad_hmean);
double gmean(double a, double b) throw(bad_gmean);
int main()
{
    using std::cout;
    using std::cin;
    using std::endl;
    
    double x, y, z;

    cout << "Enter two numbers: ";
    while (cin >> x >> y)
    {
        try {                  // start of try block
            z = hmean(x,y);
            cout << "Harmonic mean of " << x << " and " << y
                << " is " << z << endl;
            cout << "Geometric mean of " << x << " and " << y
                << " is " << gmean(x,y) << endl;
            cout << "Enter next set of numbers <q to quit>: ";
        }// end of try block
        catch (logic_error & bg)    // start of catch block
        {
			bg.show_error();
            cout << "I am so sorry, you can not do it again.\n";
            break;
        }                  
    }
    cout << "Bye!\n";
	system("pause");
    return 0;
}

double hmean(double a, double b) throw(bad_hmean)
{
    if (a == -b)
        throw bad_hmean(a,b);
    return 2.0 * a * b / (a + b);
}

double gmean(double a, double b) throw(bad_gmean)
{
    if (a < 0 || b < 0)
        throw bad_gmean(a,b);
    return std::sqrt(a * b); 
}

