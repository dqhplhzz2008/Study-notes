#ifndef QUEUETP_H_
#define QUEUETP_H_
#include <iostream>
#include<string>
using namespace std;

//Worker类
class Worker
{
private:
	string fullname;
	long id;
public:
	Worker() :fullname("no one"), id(0L) {}
	Worker(const string & s, long n) :fullname(s), id(n) {}
	~Worker() {}
	void Set();
	void Show() const;
};

//队列模板
template<class T>
class Queuetp
{
private:
	struct Node { T item; struct Node * next; };
	Node * front;
	Node * rear;
	int items;
	const int qsize;
	Queuetp(const Queuetp & q) :qsize(0) {};
	Queuetp & operator=(const Queuetp & q) { return *this; };
public:
	Queuetp(int qs = 10);
	~Queuetp();
	bool isempty()const;
	bool isfull()const;
	int queuecount()const;
	bool enqueue(const T & item);
	bool dequeue(T & item);
};

//接下来写Queuetp模板的函数
template<class T>
Queuetp<T>::Queuetp(int qs):qsize(qs)
{
	front = rear = NULL;
	items = 0;

}

template<class T>
Queuetp<T>::~Queuetp()
{
	Node *temp;
	while (front != NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}

template<class T>
bool Queuetp<T>::isempty() const
{
	return items == 0;
}

template<class T>
bool Queuetp<T>::isfull() const
{
	return items == qsize;
}

template<class T>
int Queuetp<T>::queuecount()const
{
	return items;
}

template<class T>
inline bool Queuetp<T>::enqueue(const T & item)
{
	if(isfull())
		return false;
	Node *add = new Node;
	if (add == NULL)
		return false;
	add->item = item;
	add->next = NULL;
	items++;
	if (front == NULL)
		fornt = add;
	else
		rear->next = add;
	rear = add;
	return true;
}

template<class T>
inline bool Queuetp<T>::dequeue(T & item)
{
	if(isempty())
		return false;
	item = front->item;
	items--;
	Node * temp;
	temp = front;
	front = front->next;
	delete temp;
	if (items == 0)
		rear = NULL;
	return true;
}



#endif // !QUEUETP_H_
