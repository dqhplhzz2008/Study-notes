#include<iostream>
using namespace std;
class Move
{
private:
	double x;
	double y;
public:
	Move(double a = 0, double b = 0);
	void showmove()const;
	Move add(const Move &m)const;
	void reset(double a = 0, double b = 0);
};
Move::Move(double a, double b)
{
	x = a;
	y = b;
}
void Move::showmove()const {
	cout << "x= " << x << endl;
	cout << "y= " << y << endl;
}
Move Move::add(const Move & m) const {
	return Move(x + m.x, y + m.y);

}
void Move::reset(double a, double b)
{
	x = a;
	y = b;
}

int main() {
	Move move1;
	cout << "Move1:\n";
	move1.showmove();
	Move move2 = Move(2.3, 1.9);
	cout << "Move2:\n";
	move2.showmove();
	move1 = move1.add(move2);
	cout << "Move1 after adding move2:\n";
	move1.showmove();
	move1.reset();
	move2.reset();
	cout << "Reset Move1:\n"; 
	move1.showmove();
	cout << "Reset Move2:\n";
	move2.showmove();
	system("pause");
	return 0;


}