//coordin.h--structure templates and function prototypes
//structure template
#ifndef COORDIN_H_//意味着仅当以前没有使用于处理器编译指令#define定义名称COORDIN_H_时，
//才处理#ifndef与#endif之间的语句。这是让它忽略除第一次包含之外的所有内容。C和C++常用
#define COORDIN_H_
//结构体
struct polar
{
	double distance;
	double angle;
};
struct rect
{
	double x;
	double y;
};
//函数原型
polar rect_to_polar(rect xypos);
void show_polar(polar dapos);
#endif // !COORDIN_H_
