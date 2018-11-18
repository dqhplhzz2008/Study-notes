#include<iostream>
#include<new>
#include<cstring>
using namespace std;

struct chaff
{
	char dross[20];
	int slag;
};
void show_struct(chaff & p);
char buffer2[500];
int main()
{
	chaff *p = new(buffer2) chaff[2];
	strcpy(p[0].dross, "Yushuai Zhang");
	strcpy(p[1].dross, "Shandong Province");
	p[0].slag = 23;
	p[1].slag = 100;
	for (int i = 0; i < 2; i++)
	{
		show_struct(p[i]);
	}

	system("pause");
	return 0;
}

void show_struct(chaff & p)
{
	cout << "Dross: " << p.dross << endl;
	cout << "SLAG: " << p.slag << endl;
	cout << endl;
}