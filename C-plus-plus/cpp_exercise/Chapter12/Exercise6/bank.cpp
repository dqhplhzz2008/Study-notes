
#include <iostream>     
#include "Test.h"  
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace FableGame;

const int MIN_PER_HR = 60;//每小时的分钟数

bool newcustomer(double x);
int main(int argc, const char * argv[])
{
	srand(time(0));//随机数种子
	cout << "Case Study: Bank of Heather Automatic Teller\n";
	cout << "Enter maximum size of queue: ";
	int qs;//队列最大长度
	cin >> qs;

	cout << "Enter the number of simulation hours: ";
	int hours;//模拟的小时数
	cin >> hours;
	int cyclelimit = MIN_PER_HR * hours;//总分钟数限制

	Item temp;
	int lastturnaways = 0;//来了没处理就离开的人
	int lastcustomers = 0;//客户数
	int lastserved = 0;//已经服务过的客户数
	int lastsum_line = 0;//队列总长度
	int lastline_wait = 0;//总的等待时间
	double perhour = 1;//每小时接收的客人

	while (true)
	{
		Queue line1(qs);
		Queue line2(qs);
		double min_per_cust = MIN_PER_HR / perhour;
		int turnaways = 0;//来了没处理就离开的人
		int customers = 0;//客户数
		int served = 0;//已经服务过的客户数
		int sum_line = 0;//队列总长度
		int line_wait = 0;//总的等待时间
		int wait_time1 = 0;//正在处理业务时间
		int wait_time2 = 0;//正在处理业务时间
		for (int cycle = 0; cycle < cyclelimit; ++cycle)
		{
			if (newcustomer(min_per_cust))
			{
				//有客户来了
				if (line1.isfull() && line2.isfull())
				{
					turnaways++;//队伍满了，离开
				}
				else
				{
					customers++; //增加客户
					temp.set(cycle);
					if (line1.queuecount() <= line2.queuecount())
					{
						line1.enqueue(temp);//加入队列1
					}
					else
					{
						line2.enqueue(temp);//加入队列2
					}
				}
			}
			if (wait_time1 <= 0 && !line1.isempty())
			{
				line1.dequeue(temp);//处理客户
				wait_time1 = temp.ptime();
				line_wait += cycle - temp.when();//等待时间
				served++;//服务的客户加1
			}
			if (wait_time1 > 0)
			{
				wait_time1--;//每分钟减1
			}
			if (wait_time2 <= 0 && !line2.isempty())
			{
				line2.dequeue(temp);//处理客户
				wait_time2 = temp.ptime();
				line_wait += cycle - temp.when();//等待时间
				served++;//服务的客户加1
			}
			if (wait_time2 > 0)
			{
				wait_time2--;//每分钟减1
			}
			sum_line += line1.queuecount();//这分钟正在等待的人数
			sum_line += line2.queuecount();//这分钟正在等待的人数
		}
		if (served > 0 && (double)line_wait / served > 1)
		{
			break;
		}
		else
		{
			lastturnaways = turnaways;
			lastcustomers = customers;
			lastserved = served;
			lastsum_line = sum_line;
			lastline_wait = line_wait;
			perhour++;
		}

	}

	if (lastcustomers > 0)
	{
		cout << "customers per hour: " << perhour << endl;
		cout << "customers accepted: " << lastcustomers << endl;
		cout << "customers served: " << lastserved << endl;
		cout << "turnsways: " << lastturnaways << endl;
		cout << "average queue size: ";
		cout.precision(2);
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout << (double)lastsum_line / cyclelimit << endl;
		cout << "average wait time: " << (double)lastline_wait / lastserved << " minutes\n";
	}
	else
	{
		cout << "No customers!\n";
	}
	cout << "Done!\n";

	system("pause");
	return 0;
}

//判断客户是否到来
bool newcustomer(double x)
{
	return (rand() * x / RAND_MAX < 1);
}


