//C++ Primer Plus(5th Edition)
//Chapter 15 Exercise 2
//Modefied By Yushuai Zhang
#include <iostream>
#include <cmath> // or math.h, unix users may need -lm flag
#include "exc_mean.h"
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
		//这种实现方式没有按照题目要求，按照题目要求的见注释的代码。
		catch (std::logic_error & hg)
		{
			cout << hg.what();
			cout << "Try again.\n";
			continue;
		}
 /*       catch (bad_hmean & bg)    // start of catch block
        {
			cout << bg.what();
            cout << "Try again.\n";
            continue;
        }                  
        catch (bad_gmean & hg) 
        {
            cout << hg.what();
            cout << "Sorry, you don't get to play any more.\n";
            break;
        } // end of catch block*/
    }
    cout << "Bye!\n";
    return 0;
}

double hmean(double a, double b) throw(bad_hmean)
{
    if (a == -b)
        throw bad_hmean("hmean() error: invalid arguments: a = -b\n");
    return 2.0 * a * b / (a + b);
}

double gmean(double a, double b) throw(bad_gmean)
{
    if (a < 0 || b < 0)
        throw bad_gmean("gmean() error: gmean() arguments should be >= 0\n");
    return std::sqrt(a * b); 
}

