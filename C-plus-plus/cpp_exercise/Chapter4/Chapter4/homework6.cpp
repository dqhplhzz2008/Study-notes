#include<iostream>
#include<string>
using namespace std;
struct CandyBar {
	string brand;
	double weight;
	int cal;
};
int main() {
	CandyBar snack[3] = { 
		{ "Mocha Munch",2.3,350 },
		{"Darily Nuts",3.6,498},
		{"Fumanduo",5.0,989}
	};
	int i;
	for (i = 0; i < 3; i++)
	{
		cout << "Brand " << (i + 1) << ":" << endl;
		cout << "Brand: " << snack[i].brand << endl;
		cout << "Weight: " << snack[i].weight << endl;
		cout << "Calario: " << snack[i].cal << endl;
	}
	system("pause");
	return 0;
}