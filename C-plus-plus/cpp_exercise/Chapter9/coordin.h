//coordin.h--structure templates and function prototypes
//structure template
#ifndef COORDIN_H_//��ζ�Ž�����ǰû��ʹ���ڴ���������ָ��#define��������COORDIN_H_ʱ��
//�Ŵ���#ifndef��#endif֮�����䡣�����������Գ���һ�ΰ���֮����������ݡ�C��C++����
#define COORDIN_H_
//�ṹ��
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
//����ԭ��
polar rect_to_polar(rect xypos);
void show_polar(polar dapos);
#endif // !COORDIN_H_
