//C++ Primer Plus(5th Edition)
//Chapter 15 Exercise 1
//Modefied By Yushuai Zhang
#include<iostream>
#include "tv.h"
int main()
{
	using std::cout;
	Tv s27;
	cout << "Initial settings for 27\" TV:\n";
	s27.settings();
	s27.onoff();
	s27.chanup();

	cout << "\nAdjusted settings for 27\" TV:\n";
	s27.settings();

	Remote grey;
	grey.set_chan(s27, 10);
	grey.volup(s27);
	grey.volup(s27);
	s27.set_remode(grey);
	cout << "\n27\" settings agter using remote: \n";
	s27.settings();
	grey.re_show();

	Tv s32(Tv::On);
	s32.set_mode();
	grey.set_chan(s32, 28);
	cout << "\n32\" settings:\n";
	s32.settings();

	system("pause");
	return 0;

}