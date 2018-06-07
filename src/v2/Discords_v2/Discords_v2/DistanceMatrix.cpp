#include <assert.h>
#include <stdio.h>
#include "DistanceMatrix.h"
#include "Utils.h"

matrix_t matrix;

matrix_t createDistanceMatrix(const long m, const long n, matrix_t timeSeriesSubsequences)
{
	matrix_t distancies = (matrix_t)__align_malloc((m - n + 1) * sizeof(series_t));
	assert(distancies != NULL);
	for (int i = 0; i < m - n + 1; i++)
	{
		distancies[i] = (series_t)__align_malloc((m - n + 1) * sizeof(item_t));
		assert(distancies[i] != NULL);
	}
	#pragma omp parallel for collapse(2) shared(distancies, timeSeriesSubsequences, n)
	for (int i = 0; i < m - n + 1; i++)
	{
		for (int j = 0; j < m - n + 1; j++)
		{
			if(j <= i - n || j >= i + n)
			{
				distancies[i][j] = distance2(timeSeriesSubsequences[i], timeSeriesSubsequences[j], n);
			}
			else
			{
				distancies[i][j] = POS_INF;
			}
		}
	}
	return distancies;
}

float findRowMinElement(const long rowIndex, const long m, const long n, const matrix_t distanceMatrix)
{
	assert(n != 0);
	float minValue = POS_INF;
	#pragma omp parallel shared(minValue)
	{
		#pragma omp for reduction(min:minValue)
		for (long i = 0; i < m - n + 1; i++)
		{
			if (distanceMatrix[rowIndex][i] < minValue)
			{
				minValue = distanceMatrix[rowIndex][i];
			}
		}
	}
	return minValue;
}

void crossOffSelfMatch(const long rowId, const int* startIndexes, const int n, matrix_t distanceMatrix)
{
	#pragma omp parallel for 
	for (int i = 0; i < n; i++)
	{
		distanceMatrix[rowId][startIndexes[i]] = POS_INF;
	}
}