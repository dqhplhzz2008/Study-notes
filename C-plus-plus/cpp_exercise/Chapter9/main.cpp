#include "golf.h"
#include <iostream>
using namespace std;
int main()
{
	golf ann;
	setgolf(ann, "Ann Birdfree", 24);
	showgolf(ann);
	golf g[5];
	int i = 0;
	while ((i < 2) && (setgolf(g[i])))
	{
		showgolf(g[i]);
		cout << "Next golf:\n";
		i++;
	}
	golf leo;
	setgolf(leo, "Shanshan Feng", 29);
	handicap(leo, 1);
	showgolf(leo);
	system("pause");
	return 0;
}