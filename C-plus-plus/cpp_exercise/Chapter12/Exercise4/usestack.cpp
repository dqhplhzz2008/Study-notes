#include "stack.h"
#include <iostream>

int main()
{
	Stack s1;  
	Stack s2(20);
	s2.push(10);
	s2.push(30);
	s2.push(200);
	Stack s3 = s2;
	Item m;
	s3.pop(m);
	std::cout << m << " is deleted from s3" << std::endl;

	s1 = s3;
	s1.pop(m);
	std::cout << m << " is deleted from s1" << std::endl;
	system("pause");
	return 0;
}