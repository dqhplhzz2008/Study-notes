//C++ Primer Plus(5th Edition)
//Chapter 15 Exercise 3
//Modefied By Yushuai Zhang
#include <iostream>
#include <cmath> 
#include<string>
/*
Ҫ��logic_error����������дһ��logic_error�࣬Ȼ����Ҫ���صĳ�Ա����Ϊ�麯����Ҳ���������show_error��
Ҫ��ʾ������������������Ҫ��logic_error����������Ա���������ڼ̳�����Ҫʹ�ã���������Ϊprotected
Ȼ��������������������д�Ϳ����ˡ��������������඼�Ǽ̳���logic_error����˿��԰�catch���Ķ���Ϊlogic_error�࣬Ȼ�����
ʵ����ʲô���ٽ��д���
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

