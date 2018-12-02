#include<iostream>
#include<cstring>
using namespace std;
struct human {
	char first[20];
	char last[20];
	char grade;
	int age;
};
int main()
{
	human *ps = new human;
	cout << "What is your first name?";
	cin.getline(ps->first, 20);
	cout << "What is your last name?";
	cin.getline(ps->last, 20);
	cout << "What letter grade do you deserve?";
	cin >> ps->grade;
	ps->grade = (ps->grade) + 1;
	cout << "What is your age?";
	cin >> (*ps).age;
	
	//Output the value
	cout << "Name: " <<ps->last << ", " << (*ps).first << endl;
	cout << "Grade: " << ps->grade << endl;
	cout << "Age: " << ps->age << endl;
	system("pause");
	return 0;
}