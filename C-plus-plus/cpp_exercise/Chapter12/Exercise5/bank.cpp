// bank.cpp -- use the Queue interface
// compile with queue.cpp
#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include "queue.h"
const int MIN_PER_HR = 60;

bool newcustomer(double x); // is there a new customer?

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ios_base;
// setting things up
    std::srand(std::time(0));    //  random initializing of rand()

    cout << "Case Study: Bank of Heather Automatic Teller\n";
    cout << "Enter maximum size of queue: ";
    int qs;
    cin >> qs;
    Queue line(qs);         // line queue holds up to qs people


    int hours=100;              //  hours of simulation
    // simulation will run 1 cycle per minute
    long cyclelimit = MIN_PER_HR * hours; // # of cycles

	Item temp;
	int lastturnaways = 0;//来了没处理就离开的人
	int lastcustomers = 0;//客户数
	int lastserved = 0;//已经服务过的客户数
	int lastsum_line = 0;//队列总长度
	int lastline_wait = 0;//总的等待时间
	double perhour = 1;//每小时接收的客人


// running the simulation
	while (true)
	{
		Queue line(qs);//队列应该放这里...
		double min_per_cust = MIN_PER_HR / perhour;
		int turnaways = 0;//来了没处理就离开的人
		int customers = 0;//客户数
		int served = 0;//已经服务过的客户数
		int sum_line = 0;//队列总长度
		int line_wait = 0;//总的等待时间
		int wait_time = 0;//正在处理业务时间
		for (int cycle = 0; cycle < cyclelimit; ++cycle)
		{
			if (newcustomer(min_per_cust))
			{
				//有客户来了
				if (line.isfull())
				{
					turnaways++;//队伍满了，离开
				}
				else
				{
					customers++; //增加客户
					temp.set(cycle);
					line.enqueue(temp);//加入队列
				}
			}
			if (wait_time <= 0 && !line.isempty())
			{
				line.dequeue(temp);//处理客户
				wait_time = temp.ptime();
				line_wait += cycle - temp.when();//等待时间
				served++;//服务的客户加1
			}
			if (wait_time > 0)
			{
				wait_time--;//每分钟减1
			}
			sum_line += line.queuecount();//这分钟正在等待的人数
		}
		if ((double)line_wait / served > 1)
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

//  x = average time, in minutes, between customers
//  return value is true if customer shows up this minute
bool newcustomer(double x)
{
    return (std::rand() * x / RAND_MAX < 1); 
}
