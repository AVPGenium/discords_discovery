/**
* Parallel discords search algorithm for Intel Xeon Phi architecture
* A module containing discords search logic
* (c) 2018 Mikhail Zymbler, Andrei Poliakov
*/

#ifndef DISCORDSRUN_H
#define DISCORDSRUN_H

#include "Config.h"

extern int bsfPos;
extern float bsfDist;
extern series_t timeSeries;

/**
* Нахождение диссонанса заданной длины в данном временном ряде
* для заданной подпоследовательности
* @input T - временной ряд
* @input m - длина временного ряда
* @input n - длина подпоследовательности
* @output bsf_dist - расстояние до ближайшего соседа
* @input threadNum - кол-во потоков, на которых запускается алгоритм
* @output time - время затраченное на выполнение алгоритма
* @return индекс начала диссонанса
*/
int findDiscord(const series_t T, const int m, const int n, float* bsf_dist, int threadNum, double* time);

/**
* Создание матрицы подпоследовательностей
* для заданной подпоследовательности
* @param T - временной ряд
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @return матрица подпоследовательностей
*/
matrix_t createSubsequencies(const series_t T, const int m, const int n);

/**
* Создание матрицы расстояний для заданной матрицы подпоследовательностей
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @param timeSeriesSubsequences - матрица подпоследовательностей
* @param threadNum - количество нитей исполнения
* @output time - время выполнения
* @return матрица расстояний
*/
matrix_t createDistanceMatrix(const int m, const int n, matrix_t timeSeriesSubsequences, int threadNum, double* time);

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
