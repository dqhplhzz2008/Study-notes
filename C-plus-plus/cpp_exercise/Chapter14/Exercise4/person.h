#ifndef PERSON_H_
#define PERSON_H_
#include <iostream>
#include <string>
#include <valarray>
#include<cstdlib>
#include<ctime>
using namespace std;
//class Person start
class Person
{
private:
	string firstname;
	string lastname;

public:
	Person() :firstname("no"), lastname("one") {};
	Person(const string & f, const string & l) :firstname(f), lastname(l) {}
	virtual ~Person() {}
	virtual void set()
	{
		cout << "Enter Last Name: ";
		getline(cin, lastname);
		cout << "Enter First name: ";
		getline(cin, firstname);
	}
	virtual void show()
	{
		cout << "Name: " << firstname << " " << lastname << endl;
	}
};
//class Person end

//class Gunslinger start
class Gunslinger :public virtual Person
{
private:
	int kehen;
	double guntime;
	void getGun()
	{
		cout << "Enter the guntime: ";
		cin >> guntime;
		cout << "Enter the kehen: ";
		cin >> kehen;
		cin.get();
	}
public:
	virtual ~Gunslinger() {}
	virtual void set()
	{
		Person::set();
		getGun();
	}
	double draw()
	{
		return guntime;
	}
	virtual void show()
	{
		Person::show();
		cout << "Kehen: " << kehen << endl;
		cout << "GunTime: " << guntime << endl;
	}
};
//class Gunslinger end

//class pokerplayer start
class PokerPlayer :virtual public Person
{
public:
	int draw()
	{
		srand(time(0));
		return rand() % 52 + 1;
	}
	virtual ~PokerPlayer() {}

};
//class pokerplayer end

//class baddude start
class BadDude :public Gunslinger, public PokerPlayer
{
public:
	double gdraw()
	{
		return Gunslinger::draw();
	}
	int cdraw()
	{
		return PokerPlayer::draw();
	}
	void show()
	{
		Gunslinger::show();
	}


};
//class baddude end
#endif // !PERSON_H_
