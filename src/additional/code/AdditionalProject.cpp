// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <malloc.h>
#include <math.h>
#include <iostream>
using namespace std;

char alphabet[4] = { 'a', 'b', 'c', 'e' };
int alphabet_size = 4;
int word_length = 3;

// Memory allocation with alignment 
#define __align_malloc(cnt)	_mm_malloc((cnt), 64)

bool NextSet(int *a, int n, int m)
{
	int j = m - 1;
	while (j >= 0 && a[j] == n)
	{
		j--;
	}
	if (j < 0)
	{
		return false;
	}
	if (a[j] >= n)
	{
		j--;
	}
	a[j]++;
	if (j == m - 1)
	{
		return true;
	}
	for (int k = j + 1; k < m; k++)
	{
		a[k] = 1;
	}
	return true;
}

void Print(int *a, int n)
{
	static int num = 1;
	cout.width(3);
	cout << num++ << ":  ";
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}

int main()
{
	long array[64][3];
	int* a = new int[word_length];
	for (int j = 0; j < word_length; j++)
	{
		a[j] = 1;
	}
	cout << powl(alphabet_size, word_length) << endl;;
	for (int i = 0; i < powl(alphabet_size, word_length); i++)
	{
		cout << endl;
		for (int j = 0; j < word_length; j++)
		{
			int current = a[j];
			array[i][j] = alphabet[a[j]-1];
		}
		NextSet(a, alphabet_size, word_length);
	}
	for (int i = 0; i < powl(alphabet_size, word_length); i++)
	{
		for (int j = 0; j < word_length; j++)
		{
			cout << (char)array[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}