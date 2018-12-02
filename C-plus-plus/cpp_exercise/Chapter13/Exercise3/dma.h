#ifndef DMA_H_
#define DMA_H_
#include<iostream>
using namespace std;
class ABC
{
public:
	ABC();
	~ABC();
	virtual void View() = 0;
};


class baseDMA : public ABC
{
private:
	char *label;
	int rating;
public:
	baseDMA(const char *l = "null", int r = 0);
	baseDMA(const baseDMA & rs);
	virtual ~baseDMA();
	baseDMA & operator=(const baseDMA &rs);
	friend std::ostream & operator<<(std::ostream & os, const baseDMA &rs);
	virtual void View();
};

class lacksDMA : public baseDMA
{
private:
	enum{COL_LEN=40};
	char color[COL_LEN];
public:
	lacksDMA(const char * c = "blank", const char *l = "null", int r = 0);
	lacksDMA(const char *c, const baseDMA &rs);
	friend std::ostream & operator<<(std::ostream & os, const lacksDMA & rs);
	virtual void View();
};

class hasDMA : public baseDMA
{
private: char *style;
public:
	hasDMA(const char *s = "none", const char * l = "null", int r = 0);
	hasDMA(const char *s, const baseDMA &rs);
	hasDMA(const hasDMA &hs);
	~hasDMA();
	hasDMA & operator=(const hasDMA & hs);
	friend std::ostream & operator<<(std::ostream&os, const hasDMA &rs);
	virtual void View();
};
#endif // !DMA_H_

