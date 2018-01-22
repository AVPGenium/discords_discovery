#include "PAA.h"
#include <iostream>
using namespace std;

int main()
{
	testPAA();
}

void testPAA()
{
	double series1[] = { 2.02, 2.33, 2.99, 6.85, 9.20, 8.80, 7.50, 6.00, 5.85, 3.85, 4.85, 3.85, 2.22, 1.45, 1.34 };
	int length = 7;
	PAA paa(length);
	paa.apply(series1, 15);
	double* result = paa.getVector();
	// 7 -> (2.23, 5.62, 8.67, 6.36, 4.58, 3.33, 1.45)
	// 9 -> (2.14, 3.63, 8.26, 8.28, 6.27, 4.65, 4.45, 2.39, 1.38)
	for (int i = 0; i < length; i++)
	{
		std::cout << result[i] << std::endl;
	}
}