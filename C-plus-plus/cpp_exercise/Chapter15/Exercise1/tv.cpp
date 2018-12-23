//C++ Primer Plus(5th Edition)
//Chapter 15 Exercise 1
//Modefied By Yushuai Zhang
#include<iostream>
#include"tv.h"
bool Tv::volup()
{
	if (volume < MaxVal)
	{
		volume++;
		return true;
	}
	else
		return false;
}

bool Tv::voldown()
{
	if (volume > MinVal)
	{
		volume--;
		return true;
	}
	return false;
}

void Tv::chanup()
{
	if (channel < maxchannel)
		channel++;
	else
		channel = 1;
}

void Tv::chandown()
{
	if (channel > 1)
		channel--;
	else
		channel = maxchannel;
}
void Tv::settings()const
{
	using std::cout;
	using std::endl;
	cout << "TV is " << (state == On? "Off" : "On" )<< endl;
	if (state == On)
	{
		cout << "Volume setting = " << volume << endl;
		cout << "Channel setting = " << channel << endl;
		cout << "Mode = "
			<< (mode == Antenna ? "antenna" : "cable") << endl;
		cout << "Input = " << (input == TV ? "TV" : "VCR") << endl;
	}
}

void Tv::set_remode(Remote & r)
{
	if (state == On)
		r.re_mode = !r.re_mode;

}

void Remote::re_show() const
{
	std::cout << "Remode = "<< (re_mode == Normal ? "Normal" : "Interact") << std::endl;
}
