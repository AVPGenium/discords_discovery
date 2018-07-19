/**
* Parallel discords search algorithm for Intel Xeon Phi architecture
* A module containing discords search logic
* (c) 2018 Mikhail Zymbler, Andrei Poliakov
*/

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "omp.h"
#include "DiscordsRun.h"
#include "SAX.h"

int bsfPos;
float bsfDist;
series_t timeSeries;
int countOfSubseq;

size_t m_string_size = 3;
size_t m_alphabet_size = 3;

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
* @return индекс начала диссонанса
*/
int findDiscord(const series_t T, const int m, const int n, float* bsf_dist, int threadNum, double* time)
{
	countOfSubseq = m - n + 1;
	// normalize
	train(T, m);
	series_t nT = normalize(T, m);
	// create matrix of subsequencies
	matrix_t timeSeriesSubsequences = createSubsequencies(nT, m, n);
	word* words = (word*)__align_malloc((countOfSubseq) * sizeof(word));
	for (long i = 0; i < countOfSubseq; i++)
	{
		words[i] = (word)__align_malloc((countOfSubseq) * sizeof(symbol));
	}

	long* minValIndexes = (long*)__align_malloc((countOfSubseq) * sizeof(long));
	long minValIndexesCount = 0;
	// indexes for corresponding to sax words subsequences
	long**wordsTable = generateWordsTable();
	long** chainsOfIndexes = (long**)__align_malloc(powl(m_alphabet_size, m_string_size) * sizeof(long*));
	for (long i = 0; i < powl(m_alphabet_size, m_string_size); i++)
	{
		chainsOfIndexes[i] = (long*)__align_malloc((countOfSubseq) * sizeof(long));
	}

	// prepare
	for (long i = 0; i < countOfSubseq; i++)
	{
		word saxWord = saxify(timeSeriesSubsequences[i], n);
		words[i] = saxWord;
		long index = hashWord(saxWord);
		chainsOfIndexes[index][wordsTable[index][m_string_size]] = i;
		// need sync in multithreading mode
		wordsTable[index][m_string_size]++;
	}

	// todo: find min indexes and put it in array

	// main stage: finding the discord
	bsfDist = 0;
	for (long i = 0; i < minValIndexesCount; i++)
	{
		double min = POS_INF;
		bool earlyExit = false;
		long chainIndex = hashWord(words[minValIndexes[i]]);
		long innerIterationsCount = wordsTable[chainIndex][m_string_size];

		for (long j = 0; j < innerIterationsCount; j++)
		{
			if (!isSelfMatch(minValIndexes[i], chainsOfIndexes[chainIndex][j], n))
			{
				double dist = distance2(timeSeriesSubsequences[minValIndexes[i]], timeSeriesSubsequences[chainsOfIndexes[chainIndex][j]], n);
				if (dist < bsfDist) {
					earlyExit = true;
					// add pragma for openmp
					break;
				}
				if (dist < min) {
					min = dist;
				}
			}
		}
		for (long j = 0; j < countOfSubseq; j++)
		{
			if (!binSearch(chainsOfIndexes[chainIndex], innerIterationsCount, j) && !isSelfMatch(minValIndexes[i], j, n))
			{
				double dist = distance2(timeSeriesSubsequences[minValIndexes[i]], timeSeriesSubsequences[j], n);
				if (dist < bsfDist) {
					earlyExit = true;
					// add pragma for openmp
					break;
				}
				if (dist < min) {
					min = dist;
				}
			}
		}
		if (!earlyExit && min > bsfDist) {
			bsfDist = min;
			bsfPos = i;
		}
	}

	for (long i = 0; i < countOfSubseq; i++)
	{
		if (!binSearch(minValIndexes, minValIndexesCount, i))
		{
			double min = POS_INF;
			bool earlyExit = false;
			long chainIndex = hashWord(words[i]);
			long innerIterationsCount = wordsTable[chainIndex][m_string_size];

			for (long j = 0; j < innerIterationsCount; j++)
			{
				if (!isSelfMatch(i, chainsOfIndexes[chainIndex][j], n))
				{
					double dist = distance2(timeSeriesSubsequences[i], timeSeriesSubsequences[chainsOfIndexes[chainIndex][j]], n);
					if (dist < bsfDist) {
						earlyExit = true;
						// add pragma for openmp
						break;
					}
					if (dist < min) {
						min = dist;
					}
				}
			}
			for (long j = 0; j < countOfSubseq; j++)
			{
				if (!binSearch(chainsOfIndexes[chainIndex], innerIterationsCount, j) && !isSelfMatch(i, j, n))
				{
					double dist = distance2(timeSeriesSubsequences[i], timeSeriesSubsequences[j], n);
					if (dist < bsfDist) {
						earlyExit = true;
						// add pragma for openmp
						break;
					}
					if (dist < min) {
						min = dist;
					}
				}
			}
			if (!earlyExit && min > bsfDist) {
				bsfDist = min;
				bsfPos = i;
			}
		}
	}
	return bsfPos;
}

/**
* Создание матрицы подпоследовательностей
* для заданной подпоследовательности
* @param T - временной ряд
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @return матрица подпоследовательностей
*/
matrix_t createSubsequencies(const series_t T, const int m, const int n)
{
	matrix_t result = (matrix_t)__align_malloc((m - n + 1) * sizeof(series_t));
	assert(result != NULL);
	for (int i = 0; i < m - n + 1; i++)
	{
		result[i] = (series_t)__align_malloc(n * sizeof(item_t));
		assert(result[i] != NULL);
	}
	for (int i = 0; i < m - n + 1; i++)
	{
		memcpy(result[i], &T[i], n * sizeof(item_t));
	}
	return result;
}

/*
 * Binary search in given array
 * Return: index of element or -1
 */
long binSearch(long* array, long size, long value)
{
	long average_index = 0; // переменная для хранения индекса среднего элемента массива
	long first_index = 0; // индекс первого элемента в массиве
	long last_index = size - 1; // индекс последнего элемента в массиве
	if (last_index == -1)
	{
		//cout << "\narray is empty" << endl; // массив пуст
		return last_index;
	}
	while (first_index < last_index)
	{
		average_index = first_index + (last_index - first_index) / 2; // меняем индекс среднего значения
		value <= array[average_index] ? last_index = average_index : first_index = average_index + 1;    // найден ключевой элемент или нет 
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

bool isSelfMatch(long i, long j, long n)
{
	return !(j <= i - n || j >= i + n);
}

/**
* Calculates the square of the Euclidean distance between two single-dimensional timeseries represented
* by the rational vectors.
* @param point1 The first timeseries.
* @param point2 The second timeseries.
* @param length The length of series.
* @return The Euclidean distance.
*/
item_t distance2(const series_t series1, const series_t series2, const int length)
{
	assert(length > 0);
	assert(series1 != NULL);
	assert(series2 != NULL);
	float sum = 0;
	MY_ASSUME_ALIGNED(series1);
	MY_ASSUME_ALIGNED(series2);
	for (int i = 0; i < length; i++)
	{
		sum += (series1[i] - series2[i]) * (series1[i] - series2[i]);
	}
	return sum;
}

/**
* Finding min element in vector
* @input series vector of data.
* @input length The length of vector.
* @output position
*/
item_t min(const series_t series, const int length, int* position)
{
	item_t result = series[0];
	for (int i = 0; i < length; i++)
	{
		if (series[i] < result)
		{
			result = series[i];
			*position = i;
		}
	}
	return result;
}

/**
* Finding max element in vector
* @input series vector of data.
* @input length The length of vector.
* @output position
*/
item_t max(const series_t series, const int length, int* position)
{
	item_t result = series[0];

	for (int i = 0; i < length; i++)
	{
		if (series[i] > result)
		{
			result = series[i];
			*position = i;
		}
	}
	return result;
}

