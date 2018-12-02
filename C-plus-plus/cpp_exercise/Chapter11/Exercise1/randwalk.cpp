#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "vector.h"
using namespace std;
using VECTOR::Vector;
int main() {
	ofstream outFile;
	outFile.open("exercise1.txt");
	srand(time(0));
	double direction;
	Vector step;
	Vector result(0.0, 0.0);
	unsigned long steps = 0;
	double target;
	double dstep;
	cout << "Enter target distance(q to quit): ";
	while (cin >> target)
	{
		cout << "Enter step length: ";
		if (!(cin >> dstep))
			break;
		outFile << "Target Distance: " << target << ", Step Size: " << dstep << endl;
		while (result.magval() < target)
		{
			direction = rand() % 360;
			step.set(dstep, direction, 'p');
			result = result + step;
			outFile << steps << ": (x,y) = " << "(" << step.xval() << ", " << step.yval() << ")" << endl;
			steps++;
		}
		outFile << "After " << steps << " steps, the subject "
			"has the following location:\n";
		outFile << "(x,y)=" << result << endl;
		result.polar_mode();
		outFile << " or\n" << result << endl;
		outFile << "Average outward distance per step = "
			<< result.magval() / steps << endl;
		outFile << "===================================================="<<endl;
		steps = 0;
		result.set(0.0, 0.0);
		cout << "Enter target distance (q to quit): ";
	}
	outFile.close();
	cout << "Bye~" << endl;
	system("pause");
	return 0;
}  