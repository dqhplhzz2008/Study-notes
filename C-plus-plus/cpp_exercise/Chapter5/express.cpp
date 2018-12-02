#include <iostream>
using namespace std;
int main() {
	int x;
	cout << "The expression x=100 has the value";
	cout << (x = 100) << endl;
	cout << "Now x = " << x << endl;
	cout << "The expression x<3 has the value";
	cout << (x < 3) << endl;
	cout << "The expression x>3 has the value";
	cout << (x > 3) << endl;
	cout.setf(ios_base::boolalpha);//a new c++ feature
	cout << "The expression x<3 has the value";
	cout << (x < 3) << endl;
	cout << "The expression x>3 has the value";
	cout << (x > 3) << endl;
	system("pause");
	return 0;
}