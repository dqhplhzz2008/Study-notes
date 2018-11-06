//C++ Primer Plus Edition 5
//Chapter 7 Homework 2
#include<iostream>
using namespace std;
const int MAXSIZE = 10;
int fill_array(double scores[], int limit);
void show_array(const double ar[], int n);
double aver_array(double arc[], int n);
int main() {
	double scores[MAXSIZE];
	double average;
	cout << "Please enter ten scores:" << endl;
	int size = fill_array(scores, MAXSIZE);
	cout << "The scores are:" << endl;
	show_array(scores, size);
	average = aver_array(scores, size);
	cout << "The average score is " << aver_array(scores, size) << endl;
	system("pause");
	return 0;
}
int fill_array(double scores[], int limit) {
	double temp;
	int i;
	for (i = 0; i < limit; i++) {
		cout << "Enter Score #" << i << ": ";
		cin >> temp;
		if (!cin) {
			cin.clear();
			while (cin.get() != '\n')
				continue;
			break;
		}
		else if (temp < 0)
			break;
		scores[i] = temp;
	}
	return i;


}
void show_array(const double ar[], int n) {
	for (int i = 0; i < n; i++) {
		cout << "Score #" << (i + 1) << ": " << ar[i] << endl;
	}
}
double aver_array(double arc[], int n) {
	double total = 0;
	double average;
	for (int i = 0; i < n; i++) {
		total += arc[i];
	}
	average = total / n;
	return average;

}