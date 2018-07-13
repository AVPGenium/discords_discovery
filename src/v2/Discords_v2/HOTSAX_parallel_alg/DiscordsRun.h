/**
* Parallel discords search algorithm for Intel Xeon Phi architecture
* A module containing discords search logic
* (c) 2018 Mikhail Zymbler, Andrei Poliakov
*/

#ifndef DISCORDSRUN_H
#define DISCORDSRUN_H

#include "Config.h"
#include <iostream>
#include <vector>

extern int bsfPos;
extern float bsfDist;
extern series_t timeSeries;

using namespace std;

/**
* Ќахождение диссонанса заданной длины в данном временном р€де
* дл€ заданной подпоследовательности
* @input T - временной р€д
* @input m - длина временного р€да
* @input n - длина подпоследовательности
* @output bsf_dist - рассто€ние до ближайшего соседа
* @input threadNum - кол-во потоков, на которых запускаетс€ алгоритм
* @output time - врем€ затраченное на выполнение алгоритма
* @return индекс начала диссонанса
*/
int findDiscord(const series_t T, const int m, const int n, float* bsf_dist, int threadNum, double* time);

/**
* —оздание матрицы подпоследовательностей
* дл€ заданной подпоследовательности
* @param T - временной р€д
* @param m - длина временного р€да
* @param n - длина подпоследовательности
* @return матрица подпоследовательностей
*/
matrix_t createSubsequencies(const series_t T, const int m, const int n);


/**
* Calculates the square of the Euclidean distance between two single-dimensional timeseries represented
* by the rational vectors.
* @param point1 The first timeseries.
* @param point2 The second timeseries.
* @param length The length of series.
* @return The Euclidean distance.
*/
item_t distance2(const series_t series1, const series_t series2, const int length);

/**
* Finding min element in vector
* @input series vector of data.
* @input length The length of vector.
* @output position
*/
item_t min(const series_t series, const int length, int* position);

/**
* Finding max element in vector
* @input series vector of data.
* @input length The length of vector.
* @output position
*/
item_t max(const series_t series, const int length, int* position);

#endif