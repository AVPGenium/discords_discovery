#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "omp.h"
#include "DiscordsRun.h"
#include "Utils.h"
#include "DistanceMatrix.h"

int bsfPos;
float bsfDist;
series_t timeSeries;



// length of full time series
int _m;
// length of one subsequence
int _n;

/* mock for tests */
void startApp()
{
	_m = 7;
}

/* Prepare initial values of time series and length of subsequencies */
void prepareConfig(const int m, const int n, const series_t T)
{
	_m = m;
	_n = n;
	timeSeries = T;
}

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
int findDiscord(const series_t T, const int m, const int n, float* bsf_dist, int threadNum, long* time)
{
	// create matrix of subsequencies
	matrix_t timeSeriesSubsequences = createSubsequencies(T, m, n);
	// calc distance matrix
	double start = omp_get_wtime();
	matrix_t distancies = createDistanceMatrix(m, n, timeSeriesSubsequences);
	double end = omp_get_wtime();
	*time += (end - start);
	item_t* mins = (item_t*)__align_malloc((m - n + 1) * sizeof(item_t));
	omp_set_nested(true);
	int* selfMatchIndexes = (int*)__align_malloc((m - n + 1) * sizeof(item_t));
	start = omp_get_wtime();
	// for each row in distance matrix find min element
	#pragma omp parallel if(threadNum > 1) num_threads(threadNum) shared(mins, distancies)
	{
			#pragma omp for firstprivate(selfMatchIndexes)
			for (int i = 0; i < m - n + 1; i++)
			{
				int countNonSelfMatch = countNonSelfMatchSubsequencies(m, n, i);
				int count = m - n + 1 - countNonSelfMatch;
				selfMatchIndexes = findSelfMatch(m, n, i);
				crossOffSelfMatch(i, selfMatchIndexes, count, distancies);
				mins[i] = findRowMinElement(i, m, n, distancies);
			}
	}
	/*printf("\nAfter cross off: \n");
	for (int i = 0; i < m - n + 1; i++)
	{
		for (int j = 0; j < m - n + 1; j++)
		{
			printf("%f ", distancies[i][j]);
		}
		printf("\n--------\n");
	}
	printf("\nMins: \n");
	for (int i = 0; i < m - n + 1; i++)
	{
		printf("%f ", mins[i]);
	}
	printf("\n--------\n");*/
	bsfDist = max(mins, m-n+1, &bsfPos);
	end = omp_get_wtime();
	*time += (end - start);
	//printf("\nmax: %f\n", bsfDist);
	*bsf_dist = bsfDist;
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
	int countNonSelfMatch = countNonSelfMatchSubsequencies(m, n, startIndex);
	int count = m - n + 1 - countNonSelfMatch;
	int* indexes = (int*)__align_malloc(count * sizeof(int));
	assert(indexes != NULL);
	int j = 0;
	if (startIndex < n)
	{
		#pragma omp for 
		for (int i = 0; i < startIndex; i++, j++)
		{
			indexes[j] = i;
		}
	}
	else
	{
		#pragma omp for 
		for (int i = startIndex - n + 1; i < startIndex; i++, j++)
		{
			indexes[j] = i;
		}
	}
	if (m - (startIndex + n) < n)
	{
		#pragma omp for 
		for (int i = startIndex; i < m - n + 1; i++, j++)
		{
			indexes[j] = i;
		}
	}
	else
	{
		#pragma omp for 
		for (int i = startIndex; i < startIndex + n; i++, j++)
		{
			indexes[j] = i;
		}
	}
	/*printf("\nSelf match for: %d\n", startIndex);
	for (int i = 0; i < j; i++)
	{
		printf("%d ", indexes[i]);
	}
	printf("\n--------\n");*/
	return indexes;
}

/**
* Нахождения количества non-self-match подпоследовательностей
* для заданной подпоследовательности
* @param m - длина временного ряда
* @param n - длина подпоследовательности
* @param p - индекс начала подпоследовательности
* @return количество non-self-match подпоследовательностей
*/
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
		result += m - (p + n) - n + 1;
	}
	return result;
}

/* mock for tests */
void prepareConfig()
{

}