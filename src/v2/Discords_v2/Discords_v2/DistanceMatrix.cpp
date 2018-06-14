#include <assert.h>
#include <stdio.h>
#include "omp.h"
#include "DistanceMatrix.h"
#include "Utils.h"

matrix_t matrix;

matrix_t createDistanceMatrix(const long m, const long n, matrix_t timeSeriesSubsequences, int threadNum, double* time)
{
	matrix_t distancies = (matrix_t)__align_malloc((m - n + 1) * sizeof(series_t));
	assert(distancies != NULL);
	int subseqCount = m - n + 1;
	for (int i = 0; i < subseqCount; i++)
	{
		distancies[i] = (series_t)__align_malloc((subseqCount) * sizeof(item_t));
		assert(distancies[i] != NULL);
	}
	double start = omp_get_wtime();
		#pragma omp parallel for simd num_threads(threadNum) 
		for (int i = 0; i < subseqCount; i++)
		{
			for (int j = 0; j < subseqCount; j++)
			{
				if (j <= i - n || j >= i + n)
				{
					distancies[i][j] = distance2(timeSeriesSubsequences[i], timeSeriesSubsequences[j], n);
				}
				else
				{
					distancies[i][j] = POS_INF;
				}
			}
		}
	double end = omp_get_wtime();
	*time += (end - start);
	return distancies;
}

float findRowMinElement(const long rowIndex, const long m, const long n, const matrix_t distanceMatrix, int threadNum)
{
	assert(n != 0);
	float minValue = POS_INF;
	int subseqCount = m - n + 1;
	#pragma omp parallel shared(minValue)
	{
		#pragma omp for simd reduction(min:minValue)
		for (long i = 0; i < subseqCount; i++)
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