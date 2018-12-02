#include<iostream>
#include"mytime3.h"
using namespace std;
int main() {
	Time aida(3, 35);
	Time tosca(2, 48);
	Time temp;
	cout << "Aida and Tosca:\n";
	cout << aida << ";" << tosca << endl;
	temp = aida + tosca;
	temp = aida*1.17;
	cout << "Aida*1.17: " << temp << endl;
	cout << "10*Tosca: " << 10 * tosca << endl;

	system("pause");
	return 0;
}