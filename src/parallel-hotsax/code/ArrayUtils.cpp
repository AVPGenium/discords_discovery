/**
* Parallel discords search algorithm for Intel Xeon Phi architecture
* Utility methods to work with arrays
* (c) 2018 Mikhail Zymbler, Andrei Poliakov
*/

#include "ArrayUtils.h"

/*
* Binary search in given array
* Input: array and it's length, value to search
* Return: index of element or -1
*/
long binSearch(long* array, long size, long value)
{
	long average_index = 0; // ���������� ��� �������� ������� �������� �������� �������
	long first_index = 0; // ������ ������� �������� � �������
	long last_index = size - 1; // ������ ���������� �������� � �������
	if (last_index == -1)
	{
		return last_index; // ������ ����
	}
	while (first_index < last_index)
	{
		average_index = first_index + (last_index - first_index) / 2; // ������ ������ �������� ��������
		value <= array[average_index] ? last_index = average_index : first_index = average_index + 1;    // ������ �������� ������� ��� ��� 
	}
	if (array[last_index] == value)
	{
		return last_index;
	}
	else
	{
		return -1;
	}
}

/*
* Sort array in asc order
* Input: array and it's length
* Output: sorted array
*/
void sortIndexes(long* array, long n)
{
	for (long i = 0; i < n - 1; i++)
	{
		for (long j = 0; j < n - i - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				int tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
}