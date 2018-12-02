//homework 7 and 8
#include<iostream>
#include<cstring>
using namespace std;
struct PizzaBar {
	char company[30];
	double diameter;//Ö±¾¶
	double weight;
};
int main() {
	PizzaBar *pizza = new PizzaBar;
	cout << "Please input the company's name:" << endl;
	cin.getline(pizza->company, 30);
	cout << "Please input the diameter of this pizza:" << endl;
	cin >> pizza->diameter;
	cout << "Please input the weight of this pizza:" << endl;
	cin >> (*pizza).weight;
	
	//Output the information of this pizza
	cout << endl;
	cout << "Company's Name: " << pizza->company << endl;
	cout << "Pizza's diameter: " << (*pizza).diameter << endl;
	cout << "Pizza's weight: " << pizza->weight << endl;
	delete pizza;

	system("pause");
	return 0;
}