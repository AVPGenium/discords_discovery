#include <string.h>
#include "DiscordsRun.h"
#include "Utils.h"
#include "DistanceMatrix.h"

int bsfPos;
float bsfDist;
series_t timeSeries;



// length of full time series
int m;
// length of one subsequence
int n;

void start()
{
	m = 7;
}

int* findSelfMatch(series_t timeSeries, long startIndex)
{
	return 0;
}

void prepareConfig(const int _m, const int _n, const series_t T)
{
	m = _m;
	n = _n;
	timeSeries = T;
}

int findDiscord(const series_t T, const int m, const int n, float* bsf_dist)
{
	matrix_t timeSeriesSubsequences = createSubsequencies(T, n);
	matrix_t distancies = createDistanceMatrix(m, n, timeSeriesSubsequences);
	item_t* mins = new float[m - n + 1];
	for (int i = 0; i < m - n + 1; i++)
	{
		int* selfMatchIndexes = findSelfMatch(m, n, i);
		crossOffSelfMatch(i, selfMatchIndexes, m - n + 1 - countNonSelfMatchSubsequencies(m, n, i), distancies);
		mins[i] =  findRowMinElement(i, n, distancies);
	}
	bsfDist = max(mins, n, &bsfPos);
	return bsfDist;
}

matrix_t createSubsequencies(const series_t T, const int n)
{
	matrix_t result = new float* [m-n+1];
	for (int i = 0; i < m - n + 1; i++)
	{
		result[i] = new float[n];
	}
	for (int i = 0; i < m - n + 1; i++)
	{
		memcpy(result[i], &T[i], n*sizeof(item_t));
	}
	return result;
}

/**
* Нахождения индексов начала self-match подпоследовательностей
* для заданной подпоследовательности.
* Сама подпоследовательность также считается self-match
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @param p - индекс начала подпоследовательности
* @return количество non-self-match подпоследовательностей
*/
int* findSelfMatch(int m, int n, long startIndex)
{
	int count = m - n + 1 - countNonSelfMatchSubsequencies(m, n, startIndex);
	int* indexes = new int[count];
	int j = 0;
	if (startIndex < n)
	{
		for (int i = 0; i < startIndex; i++, j++)
		{
			indexes[j] = i;
		}
	}
	else
	{
		for (int i = startIndex - n + 1; i < startIndex; i++, j++)
		{
			indexes[j] = i;
		}
	}
	if (m - (startIndex + n) < n)
	{
		for (int i = startIndex; i < m - n + 1; i++, j++)
		{
			indexes[j] = i;
		}
	}
	else
	{
		for (int i = startIndex; i < startIndex + n; i++, j++)
		{
			indexes[j] = i;
		}
	}
	return indexes;
}

int countNonSelfMatchSubsequencies(int m, int n, int p)
{
	int result = 0;
	// подпоследовательностей перед заданной
	if (p >= n)
	{
		result += p - n + 1;
	}
	// подпоследовательностей после заданной
	if (m - (p + n) >= n)
	{
		result += m - (p + n) - 1;
	}
	return result;
}