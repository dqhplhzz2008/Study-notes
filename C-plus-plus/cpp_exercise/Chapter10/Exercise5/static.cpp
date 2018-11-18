#include <iostream>
#include "stack.h"
using namespace std;
Stack::Stack() 
{
	top = 0;
	total = 0;
}

Stack::~Stack()
{
	cout << "Bye!\n";
}

bool Stack::isempty()const
{
	return top == 0;
}

bool Stack::isfull()const
{
	return top == MAX;
}

bool Stack::push(const Item & item)
{
	if (top < MAX)
	{
		items[top++] = item;
		return true;
	}
	else
		return false;
}

bool Stack::pop(Item & item)
{
	if (top > 0)
	{
		item = items[--top];
		total +=item.payment;
		cout << "PO#" << item.fullname << endl;
		cout << "Total = " << total << endl;
		return true;
	}
	else
		return false;
}