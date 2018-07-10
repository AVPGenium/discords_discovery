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
	matrix_t timeSeriesSubsequences = createSubsequencies(T, m, n);
	word* words = (word*)__align_malloc((countOfSubseq) * sizeof(word));
	
	// prepare
	for (long i = 0; i < countOfSubseq; i++)
	{
		word saxWord = saxify(timeSeriesSubsequences[i]);
		words[i] = saxWord;
		tree.addNode(saxWord, i);
	}
	for(int p = 1; p < countOfSubseq; p++) {
		double min = POS_INF;
		bool earlyExit = false;
		for(int j = 0; j < countOfSubseq; j++) {
			if (!isSelfMatch(𝑝, 𝑗) {
				double dist = dist2(𝑝, 𝑗);
				if (dist < best_so_far_dist) {
					earlyExit = true;
					break;
				}
				if (dist < min) {
					min = dist;
				}
			}
		}
		if(!earlyExit && min > best_so_far_dist) {
			best_so_far_dist = min;
			best_so_far_pos = p;
		}
	}
	return 0;
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