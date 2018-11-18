#ifndef GOLF_H
#define GOLF_H
class Golf {
private:
	static const int Len = 40;
	char fullname[Len];
	int handicap;
public:
	Golf(const char * name = "HHHHHH", int hc = 10);
	~Golf();
	bool setGolf();
	void sethandicap(int hc);
	void showGolf()const;
};
#endif // GOLF_H