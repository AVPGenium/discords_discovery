#include <assert.h>
#include <stdio.h>
#include "DistanceMatrix.h"
#include "Utils.h"

matrix_t matrix;

matrix_t createDistanceMatrix(const long m, const long n, matrix_t timeSeriesSubsequences)
{
	matrix_t distancies = new float*[m - n + 1];
	assert(distancies != NULL);
	for (int i = 0; i < m - n + 1; i++)
	{
		distancies[i] = new float[m - n + 1];
	}
	for (int i = 0; i < m - n + 1; i++)
	{
		for (int j = 0; j < m - n + 1; j++)
		{
			distancies[i][j] = distance2(timeSeriesSubsequences[i], timeSeriesSubsequences[j], n);
			printf("%f ", distancies[i][j]);
		}
		printf("\n--------\n");
	}
	return distancies;
}

float findRowMinElement(const long rowIndex, const long m, const long n, const matrix_t distanceMatrix)
{
	assert(n != 0);
	float min = distanceMatrix[rowIndex][0];
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
	for (int i = 0; i < n; i++)
	{
		distanceMatrix[rowId][startIndexes[i]] = POS_INF;
	}
}