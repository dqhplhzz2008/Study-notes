//C++ Primer Plus(5th Edition)
//Chapter 15 Exercise 1
//Modefied By Yushuai Zhang
#ifndef TV_H_
class Tv
{
public:
	friend class Remote;
	enum{Off, On};
	enum{MinVal,MaxVal=20};
	enum{Antenna,Cable};
	enum{TV,VCR};

	Tv(int s = Off, int mc = 100) :state(s), volume(5), maxchannel(mc), channel(2), mode(Cable), input(TV) {}
	void onoff() {
		state = (state == On) ? Off : On;
	}
	bool ison()const { return state == On; }
	bool volup();
	bool voldown();
	void chanup();
	void chandown();
	void set_mode() { mode = (mode == Antenna) ? Cable : Antenna; }
	void set_input() { input = (input == TV)? VCR : TV; }
	void settings()const;
	void set_remode(Remote & r);//在Tv类中添加一个对Remote中新成员进行切换的方法
private:
	int state;
	int volume;
	int maxchannel;
	int channel;
	int mode;
	int input;
};

class Remote
{
private:
	int mode;
public:
	int re_mode;//新增的状态变量成员
	friend class Tv;
	Remote(int m = Tv::TV):mode(m),re_mode(Normal){}
	bool volup(Tv & t) { return t.volup(); }
	bool voldown(Tv & t) { return t.voldown(); }
	void onoff(Tv & t) { t.onoff(); }
	void chanup(Tv & t) { t.chanup(); }
	void chandown(Tv & t) { t.chandown(); }
	void set_chan(Tv &t, int c) { t.channel = c; }
	void set_mode(Tv & t) { t.set_mode(); }
	void set_input(Tv & t) { t.set_input(); }
	void re_show()const;
	enum { Normal, Interact };//遥控器处于正常还是交互
};
#endif // !TV_H_
