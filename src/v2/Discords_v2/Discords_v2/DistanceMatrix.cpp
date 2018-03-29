#include <assert.h>
#include "DistanceMatrix.h"
#include "Utils.h"

matrix_t matrix;

matrix_t createDistanceMatrix(const long m, const long n, matrix_t timeSeriesSubsequences)
{
	return 0;
}

float findRowMinElement(const long rowIndex, const long n, const matrix_t distanceMatrix)
{
	assert(n != 0);
	float min = distanceMatrix[rowIndex][0];
	for (long i = 1; i < n; i++)
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