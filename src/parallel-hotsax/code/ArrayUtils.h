/**
* Parallel discords search algorithm for Intel Xeon Phi architecture
* Utility methods to work with arrays
* (c) 2018 Mikhail Zymbler, Andrei Poliakov
*/

#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

/*
* Binary search in given array
* Return: index of element or -1
*/
long binSearch(long* array, long size, long value);

/*
* Sort array with indexes in asc order
* Input: array and it's length
* Output: sorted array
*/
void sortIndexes(long* array, long n);

#endif