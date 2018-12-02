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
	int lastturnaways = 0;//����û������뿪����
	int lastcustomers = 0;//�ͻ���
	int lastserved = 0;//�Ѿ�������Ŀͻ���
	int lastsum_line = 0;//�����ܳ���
	int lastline_wait = 0;//�ܵĵȴ�ʱ��
	double perhour = 1;//ÿСʱ���յĿ���


// running the simulation
	while (true)
	{
		Queue line(qs);//����Ӧ�÷�����...
		double min_per_cust = MIN_PER_HR / perhour;
		int turnaways = 0;//����û������뿪����
		int customers = 0;//�ͻ���
		int served = 0;//�Ѿ�������Ŀͻ���
		int sum_line = 0;//�����ܳ���
		int line_wait = 0;//�ܵĵȴ�ʱ��
		int wait_time = 0;//���ڴ���ҵ��ʱ��
		for (int cycle = 0; cycle < cyclelimit; ++cycle)
		{
			if (newcustomer(min_per_cust))
			{
				//�пͻ�����
				if (line.isfull())
				{
					turnaways++;//�������ˣ��뿪
				}
				else
				{
					customers++; //���ӿͻ�
					temp.set(cycle);
					line.enqueue(temp);//�������
				}
			}
			if (wait_time <= 0 && !line.isempty())
			{
				line.dequeue(temp);//����ͻ�
				wait_time = temp.ptime();
				line_wait += cycle - temp.when();//�ȴ�ʱ��
				served++;//����Ŀͻ���1
			}
			if (wait_time > 0)
			{
				wait_time--;//ÿ���Ӽ�1
			}
			sum_line += line.queuecount();//��������ڵȴ�������
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
