/*
* Module containing methods for working with the distance matrix
*/

#ifndef DISTANCE_MATRIX_H
#define DISTANCE_MATRIX_H

#include "Config.h"

extern matrix_t matrix;

/**
* Создание матрицы расстояний для заданной матрицы подпоследовательностей
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @param timeSeriesSubsequences - матрица подпоследовательностей
* @return матрица расстояний
*/
matrix_t createDistanceMatrix(const long m, const long n, matrix_t timeSeriesSubsequences);

/**
* Нахождение минимального элемента ряда матрицы
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @param timeSeriesSubsequences - матрица подпоследовательностей
* @return матрица расстояний
*/
float findRowMinElement(const long rowIndex, const long m, const long n, const matrix_t distanceMatrix);

/**
* Вычеркивание элементов ряда матрицы, являющихся самоподобными
* @param rowId - индекс ряда матрицы
* @param startIndexes - индексы вычеркиваемых подпоследовательностей
* @param n - длина подпоследовательности
* @param distanceMatrix - матрица расстояний
* @return матрица расстояний
*/
void crossOffSelfMatch(const long rowId, const int* startIndexes, const int n, matrix_t distanceMatrix);

#endif
