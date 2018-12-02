
#include <iostream>     
#include "Test.h"  
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace FableGame;

const int MIN_PER_HR = 60;//ÿСʱ�ķ�����

bool newcustomer(double x);
int main(int argc, const char * argv[])
{
	srand(time(0));//���������
	cout << "Case Study: Bank of Heather Automatic Teller\n";
	cout << "Enter maximum size of queue: ";
	int qs;//������󳤶�
	cin >> qs;

	cout << "Enter the number of simulation hours: ";
	int hours;//ģ���Сʱ��
	cin >> hours;
	int cyclelimit = MIN_PER_HR * hours;//�ܷ���������

	Item temp;
	int lastturnaways = 0;//����û������뿪����
	int lastcustomers = 0;//�ͻ���
	int lastserved = 0;//�Ѿ�������Ŀͻ���
	int lastsum_line = 0;//�����ܳ���
	int lastline_wait = 0;//�ܵĵȴ�ʱ��
	double perhour = 1;//ÿСʱ���յĿ���

	while (true)
	{
		Queue line1(qs);
		Queue line2(qs);
		double min_per_cust = MIN_PER_HR / perhour;
		int turnaways = 0;//����û������뿪����
		int customers = 0;//�ͻ���
		int served = 0;//�Ѿ�������Ŀͻ���
		int sum_line = 0;//�����ܳ���
		int line_wait = 0;//�ܵĵȴ�ʱ��
		int wait_time1 = 0;//���ڴ���ҵ��ʱ��
		int wait_time2 = 0;//���ڴ���ҵ��ʱ��
		for (int cycle = 0; cycle < cyclelimit; ++cycle)
		{
			if (newcustomer(min_per_cust))
			{
				//�пͻ�����
				if (line1.isfull() && line2.isfull())
				{
					turnaways++;//�������ˣ��뿪
				}
				else
				{
					customers++; //���ӿͻ�
					temp.set(cycle);
					if (line1.queuecount() <= line2.queuecount())
					{
						line1.enqueue(temp);//�������1
					}
					else
					{
						line2.enqueue(temp);//�������2
					}
				}
			}
			if (wait_time1 <= 0 && !line1.isempty())
			{
				line1.dequeue(temp);//����ͻ�
				wait_time1 = temp.ptime();
				line_wait += cycle - temp.when();//�ȴ�ʱ��
				served++;//����Ŀͻ���1
			}
			if (wait_time1 > 0)
			{
				wait_time1--;//ÿ���Ӽ�1
			}
			if (wait_time2 <= 0 && !line2.isempty())
			{
				line2.dequeue(temp);//����ͻ�
				wait_time2 = temp.ptime();
				line_wait += cycle - temp.when();//�ȴ�ʱ��
				served++;//����Ŀͻ���1
			}
			if (wait_time2 > 0)
			{
				wait_time2--;//ÿ���Ӽ�1
			}
			sum_line += line1.queuecount();//��������ڵȴ�������
			sum_line += line2.queuecount();//��������ڵȴ�������
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

//�жϿͻ��Ƿ���
bool newcustomer(double x)
{
	return (rand() * x / RAND_MAX < 1);
}


