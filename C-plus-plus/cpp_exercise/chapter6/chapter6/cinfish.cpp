#include<iostream>
using namespace std;
const int Max = 5;
int main(){
	double fish[Max];
	cout << "You may enter up to " << Max << "fish <q to terminate>.\n";
	cout << "fish #1:";
	int i = 0;
	while (i<Max&&cin >> fish[i])
	{
		if (++i < Max)
			cout << "fish #" << i + 1 << ": ";
	}
	double total = 0.0;
	for (int j = 0; j < Max; j++)
		total += fish[j];
	if (i == 0)
		cout << "No fish\n";
	else
		cout << total / i << "=average weight of " << i << " fish\n";
	cout << "Done\n";
	system("pause");
	return 0;
}