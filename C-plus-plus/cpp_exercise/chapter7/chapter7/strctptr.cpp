#include<iostream>
#include<cmath>
using namespace std;
struct polar {
	double distance;
	double angle;
};
struct rect {
	double x;
	double y;
};
void rect_to_polar(const rect *xypos, polar *pda);//前面的不能修改，后面的需要修改
void show_polar(const polar *dapos);
int main() {
	rect rplace;
	polar pplace;

	cout << "Enter the x and y values";
	while (cin >> rplace.x >> rplace.y)
	{
		rect_to_polar(&rplace,&pplace);
		show_polar(&pplace);
		cout << "Next two number(q to quit)";
	}
	cout << "Done.\n";

	system("pause");
	return 0;
}

void rect_to_polar(const rect *xypos,polar *pda) {
	(*pda).distance = sqrt((*xypos).x*(*xypos).x + (*xypos).y * (*xypos).y);
	(*pda).angle = atan2((*xypos).y, (*xypos).x);

}
void show_polar(const polar *dapos) {
	const double Rad_to_deg = 57.29577951;
	cout << "distance = " << (*dapos).distance;
	cout << ", angle = " << (*dapos).angle*Rad_to_deg;
	cout << " degrees\n";
}