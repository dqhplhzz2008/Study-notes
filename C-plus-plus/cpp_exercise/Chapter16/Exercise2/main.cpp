//C++ Primer Plus(5th Edition)
//Chapter 16 Exercise 2
//Designed by YushuaiZhang
#include<iostream>
#include<string>
#include<cctype>
using namespace std;
bool is_hui(const string & st);
int main()
{
	string input;
	int index = 0;
	cout << "Enter words(q to quit):\n";
	while (getline(cin, input) && input != "q")
	{
		while ((index = input.find(' ', index)) != string::npos)//ȥ���ո�
		{
			input.erase(index, 1);
		 }
		cout << "The input is " << input << endl;//��֤ȥ�����
		if (is_hui(input))
			cout << "True\n";
		else
			cout << "False\n";

		cout << "Enter another words(q to quit):\n";
	}
	cout << "Done!\n";
	system("pause");
	return 0;
}
bool is_hui(const string & st)
{//������˵ķ���
	string temp;
	int i = 0;
	int j = st.size() - 1;
	for (; j >= 0; j--)
	{
		if (isalpha(st[j]))
		{
			temp.push_back(tolower(st[j]));
			i++;
		}
	}
	string temp2(temp.rbegin(), temp.rend());
	if (temp == temp2)
		return true;
	return false;
}

/*�Լ��ķ�������
bool is_hui(const string & st)
{
	string temp;//ͳһΪСд��ȥ������ĸ����
	int size_o = st.size();
	int k = 0;
	for (int j = 0; j < size_o; j++)
	{
		if (isalpha(st[j]))
		{
			temp[k] = tolower(st[j]);
			k++;
		}
	}	
	int size = temp.length();
	if (size % 2 == 0)
	{
		for (int i = 0; i < (size / 2); i++)
			if (temp[i] != temp[size - 1 - i])
				return false;
	}
	else if (size % 2 == 1)
	{
		for (int i = 0; i <= (size / 2); i++)
			if (temp[i] != temp[size - 1 - i])
				return false;
	}
	return true;
}*/