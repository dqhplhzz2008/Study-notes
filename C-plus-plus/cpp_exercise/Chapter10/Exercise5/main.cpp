#include <iostream>
#include <cctype>
#include "stack.h"

int main()
{
	using namespace std;
	Stack st;   // create an empty stack
	char ch;
	CUSTOMER po;
	cout << "Please enter A to add a purchase order.\n"
		<< "P to process a PO,or Q to quit.\n";
	while (cin >> ch && toupper(ch) != 'Q')
	{
		while (cin.get() != '\n')
			continue;
		if (!isalpha(ch))
		{
			cout << '\a';
			continue;
		}
		switch (ch)
		{
		case 'A':
		case 'a':
			cout << "Enter a PO fullname to add:\t";
			cin.getline(po.fullname, 35);
			cout << "Enter a PO payment to add:\t";
			cin >> po.payment;
			if (st.isfull())
				cout << "stack already full\n";
			else
				st.push(po);
			break;
		case 'P':
		case 'p':if (st.isempty())
			cout << "Stack already empty\n";
				 else
					 st.pop(po);
			break;
		}
		cout << "Please enter A to add a purchase order,\n"
			<< "P to process a PO, or Q to quit.\n";
	}
	cout << "Bye\n";
	return 0;
}