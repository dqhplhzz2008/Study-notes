//C++ Primer Plus Edition 5
//Chapter 6 Homework 4
#include<iostream>
#include<cctype>
using namespace std;
//函数
void showmenu();
void dis_by_name();
void dis_by_title();
void dis_by_bop();
void dis_by_pre();
//定义常量
const int strsize = 30;
const int NUM = 5;
//定义结构体
struct bop {
	char fullname[strsize];
	char title[strsize];
	char bopname[strsize];
	int preference;//0=fullname,1=title,2=bopname
};
bop people[5] = {
	{
		"Wimp Macho",
		"BOSS",
		"WM",
		0
	},
	{
		"Raki Rhodes",
		"Manager",
		"Junior Programmer",
		2
	},
	{
		"Celia Laiter",
		"MIPS",
		"CL",
		1
	},
	{
		"Hoppy Hipman",
		"Analyst Trainee",
		"AT",
		1
	},
	{
		"Pat Hand",
		"Student",
		"LOOPY",
		2
	}
};
char ch;
//开始主函数
int main() {
	showmenu();
	cin >> ch;
	while ((ch != 'a') && (ch != 'b') && (ch != 'c') && (ch != 'd') && (ch != 'q'))
	{
		showmenu();
		//cin.get(choice);
		cin.ignore();
	}
	while (ch != 'q') {
		switch (ch)
		{
		case 'a':
			dis_by_name();
			break;
		case 'b':
			dis_by_title();
			break;
		case 'c':
			dis_by_bop();
			break;
		case 'd':
			dis_by_pre();
			break;
		default:
			break;
		}
		cout << "Next choice:" << endl;
		cin >> ch;
		while ((ch != 'a') && (ch != 'b') && (ch != 'c') && (ch != 'd') && (ch != 'q'))
		{
			showmenu();
			//cin.get(choice);
			cin.ignore();
		}

	}
	cout << "Bye!" << endl;
	system("pause");
	return 0;
}

void showmenu() {
	cout << "Please enter one of the following choices.\n"
		"a)display by name				b)display by title\n"
		"c)display by bopname			d)display by preference\n"
		"q)game\n";
}
void dis_by_name() {
	for (int i = 0; i < NUM; ++i)
	{
		cout << people[i].fullname << endl;
	}
}
void dis_by_title() {
	for (int i = 0; i < NUM; ++i)
	{
		cout << people[i].title << endl;
	}
}
void dis_by_bop() {
	for (int i = 0; i < NUM; ++i)
	{
		cout << people[i].bopname << endl;
	}
}
void dis_by_pre() {
	for (int i = 0; i < NUM; ++i) {
		if(people[i].preference==0)
			cout << people[i].fullname << endl;
		else if(people[i].preference==1)
			cout<< people[i].title << endl;
		else
			cout << people[i].bopname << endl;
	}
}