#include<iostream>
#include<ctime>
int main()
{
	using namespace std;
	cout << "Enter the delay time, in seconds:";
	float secs;
	cin >> secs;
	clock_t delay_time = secs*CLOCKS_PER_SEC;
	cout << "starting...\a\n";
	clock_t start = clock();
	while (clock() - start < delay_time);
	cout << "done\a\n";
	system("pause");
	return 0;
}