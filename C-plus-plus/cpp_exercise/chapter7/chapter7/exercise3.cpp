//C++ Primer Plus Edition 5
//Chapter 7 Homework 3
#include<iostream>
using namespace std;
struct box {
	char maker[40];
	float height;
	float width;
	float length;
	float volume;
};
void show_box(box member);
void set_box(box *pmember);
int main() {
	box b = { "Yu Shuai",3,2,1,1 };
	show_box(b);
	set_box(&b);
	show_box(b);
	system("pause");
	return 0;
}
void show_box(box member) {
	cout << "Box's Maker: " << member.maker << endl;
	cout << "Box's height: " << member.height << endl;
	cout << "Box's width: " << member.width << endl;
	cout << "Box's length: " << member.length << endl;
	cout << "Box's volume: " << member.volume << endl;
}

void set_box(box *pmember) {
	(*pmember).volume = (*pmember).height*(*pmember).length*(*pmember).width;
}