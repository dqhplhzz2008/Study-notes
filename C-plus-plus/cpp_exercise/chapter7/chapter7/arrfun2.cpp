#include<iostream>
const int ArSize = 8;
int sum_Arr(int arr[], int n);
int main() {
	int cookies[ArSize] = { 1,2,4,8,16,32,64,128 };
	std::cout << cookies << " = array address,";
	std::cout << sizeof cookies << " sizeof cookies\n";//sizeof objectÊÇsizeof ¶ÔÏó
	int sum = sum_Arr(cookies, ArSize);
	std::cout << "Total cookies eaten: " << sum << std::endl;
	sum = sum_Arr(cookies, 3);
	std::cout << "First three eaters ate " << sum << std::endl;
	sum = sum_Arr(cookies + 4, 4);
	std::cout << "Last four eaters ate " << sum << " cookies.\n";
	system("pause");
	return 0;
}

int sum_Arr(int arr[], int n) {
	int total = 0;
	std::cout << arr << " = arr, ";
	std::cout << sizeof arr << " =sizeof arr\n";
	for (int i = 0; i < n; i++)
		total += arr[i];
	return total;
}