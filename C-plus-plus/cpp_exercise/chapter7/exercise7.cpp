//C++ Primer Plus Edition 5
//Chapter 7 Homework 7
#include<iostream>
using namespace std;
const int Max = 5;
double* fill_array(double *ar, double *limit);
void show_array(const double *ar, double *n);
void revalue(double r, double *ar, double *n);

int main() {
	double properties[Max];
	double *size = fill_array(properties, properties+Max);
	show_array(properties, size);
	cout << "Enter revaluation factor: ";
	double factor;
	cin >> factor;
	revalue(factor, properties, size);
	show_array(properties, size);
	cout << "Done.\n";
	system("pause");
	return 0;
}
double *fill_array(double *ar, double *limit) {
	double temp;
	double *p;
	for (p=ar; p < limit; p++) {
		cout << "Enter value: ";
		cin >> temp;
		if (!cin) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			cout << "Bad input;input process terminated.\n";
			break;
		}
		else if (temp < 0)
			break;
		*p = temp;
	}
	return p;
}

void show_array(const double *ar, double *n) {
	for (const double *p = ar; p < n; p++)
	{
		cout << "Property: $";
		cout << *p << endl;
	}
}

void revalue(double r, double *ar, double *n) {
	for (ar; ar < n; ar++)
		(*ar) *= r;
}