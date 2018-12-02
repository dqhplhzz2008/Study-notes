#include "queuetp.h"
const int SIZE = 5;
int main()
{
	using std::cout;
	using std::cin;
	using std::endl;
	Queuetp<Worker*>lolas(SIZE);
	Worker *temp;
	int n;
	char ch;
	cout << "Enter the command:\n"
		<< "A or a enter queue, "
		<< "P or p delete queue, "
		<< "Q or q quit.\n";
	while ((cin >> ch) && ch != 'q' && ch != 'Q')
	{
		while (strchr("apqAPQ", ch) == nullptr)
		{
			cout << "Please enter a p or q: ";
			cin >> ch;
		}
		switch (ch)
		{
		case 'a':
		case 'A':
			temp = new Worker;
			cin.get();
			temp->Set();
			if (lolas.isfull())
				cout << "Queue already full\n";
			else
				lolas.enqueue(temp);
			break;
		case'p':
		case'P':
			if (lolas.isempty())
				cout << "Queue already empty\n";
			else
				lolas.dequeue(temp);
			break;
		}
		cout << "Please enter a p or q: ";
	}
	cout << "\nHere the total count: ";
	cout << lolas.queuecount();
	cout << "\nDone\n"
		<< "Bye";
	cin.get();
	cin.get();
	return 0;
}