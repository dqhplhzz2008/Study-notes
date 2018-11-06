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
polar rect_to_polar(rect xypos);
void show_polar(polar dapos);
int main() {
	rect rplace;
	polar pplace;

	cout << "Enter the x and y values";
	while (cin >> rplace.x >> rplace.y)
	{
		pplace = rect_to_polar(rplace);
		show_polar(pplace);
		cout << "Next two number(q to quit)";
	}
	cout << "Done.\n";

	system("pause");
	return 0;
}

polar rect_to_polar(rect xypos) {
	polar answer;
	answer.distance = sqrt(xypos.x*xypos.x + xypos.y * xypos.y);
	answer.angle = atan2(xypos.y, xypos.x);
	return answer;

}
void show_polar(polar dapos) {
	const double Rad_to_deg = 57.29577951;
	cout << "distance = " << dapos.distance;
	cout << ", angle = " << dapos.angle*Rad_to_deg;
	cout << " degrees\n";
}