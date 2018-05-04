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
	#pragma omp for
	for (int i = 0; i < m - n + 1; i++)
	{
		#pragma omp for
		for (int j = 0; j < m - n + 1; j++)
		{
			distancies[i][j] = distance2(timeSeriesSubsequences[i], timeSeriesSubsequences[j], n);
			//printf("%f ", distancies[i][j]);
		}
		//printf("\n--------\n");
	}
	return distancies;
}

float findRowMinElement(const long rowIndex, const long m, const long n, const matrix_t distanceMatrix)
{
	assert(n != 0);
	float min = distanceMatrix[rowIndex][0];
	#pragma omp for
	for (long i = 1; i < m - n + 1; i++)
	{
		if (distanceMatrix[rowIndex][i] < min)
		{
			min = distanceMatrix[rowIndex][i];
		}
	}
	return min;
}

void crossOffSelfMatch(const long rowId, const int* startIndexes, const int n, matrix_t distanceMatrix)
{
	#pragma omp for
	for (int i = 0; i < n; i++)
	{
		distanceMatrix[rowId][startIndexes[i]] = POS_INF;
	}
}