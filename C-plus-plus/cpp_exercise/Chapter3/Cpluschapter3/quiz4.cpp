#include <stdio.h>
#include <iostream>
using namespace std;
int main() {
	long time;
	int sec, min, days,hours;
	const int transfer1 = 60;
	const int transfer2 = 24;
	cout << "Enter the number of seconds:";
	cin >> time;
	min = time / transfer1;
	sec = time%transfer1;
	hours = min / transfer1;
	min = min%transfer1;
	days = hours / transfer2;
	hours = hours%transfer2;

	cout << time << " seconds = " << days << " days, " << hours << " hours£¬" << min << " minutes, " << sec << " seconds." << endl;
	system("pause");
	return 0;
	

}