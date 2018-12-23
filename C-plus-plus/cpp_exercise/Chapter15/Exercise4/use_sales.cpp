//C++ Primer Plus(5th Edition)
//Chapter 15 Exercise 4
//Modefied By Yushuai Zhang
#include <iostream>
#include "sales.h"
#include <cmath>

int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    double vals1[12] =
    {
        1220, 1100, 1122, 2212, 1232, 2334,
        2884, 2393, 3302, 2922, 3002, 3544
    };

    double vals2[12] =
    {
        12, 11, 22, 21, 32, 34,
        28, 29, 33, 29, 32, 35
    };

    Sales sales1(2004, vals1, 12);
    LabeledSales sales2("Blogstar",2005, vals2, 12 );

    cout << "First try block:\n";
    try
    {
        int i;
        cout << "Year = " << sales1.Year() << endl;
        for (i = 0; i < 12; ++i)
        {

            cout << sales1[i] << ' ';
            if (i % 6 == 5)
                cout << endl;
        }
        cout << "Year = " << sales2.Year() << endl;
        cout << "Label = " << sales2.Label() << endl;
        for (i = 0; i <= 12; ++i)
        {

            cout << sales2[i] << ' ';
            if (i % 6 == 5)
                cout << endl;
        }
        cout << "End of try block 1.\n";
   }
   catch(std::logic_error & bad)
   {
	   cout << bad.what();
	   if (LabeledSales::nbad_index *nb = dynamic_cast<LabeledSales::nbad_index *>(&bad))
	   {
		   cout << "Company: " << nb->label_val() << endl;
		   cout << "bad index: " << nb->bi_val() << endl;
	   }
	   else if(Sales::bad_index *bi = dynamic_cast<Sales::bad_index *>(&bad))
	   {
		   cout << "bad index: " << bi->bi_val() << endl;
	   }
   }
   cout << "\nNext try block:\n";
   try
    {
        sales2[2] = 37.5;
        sales1[20] = 23345;
        cout << "End of try block 2.\n";
   }
   catch(std::logic_error & bad)
   {
	   cout << bad.what();
	   if (LabeledSales::nbad_index *nb = dynamic_cast<LabeledSales::nbad_index *>(&bad))
	   {
		   cout << "Company: " << nb->label_val() << endl;
		   cout << "bad index: " << nb->bi_val() << endl;
	   }
	   else if (Sales::bad_index *bi = dynamic_cast<Sales::bad_index *>(&bad))
	   {
		   cout << "bad index: " << bi->bi_val() << endl;
	   }
   }
   cout << "done\n";
   system("pause");
   return 0;
}
